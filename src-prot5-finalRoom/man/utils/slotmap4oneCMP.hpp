#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <cassert>

#include "../../cmp/components.hpp"

#define Capacity 10

struct Slotmap {
public:
    
    using   key_type = struct { std::uint32_t id; std::uint32_t gen; };
    using   iterator = RenderCMP*;
    using  citerator = RenderCMP const*;

    explicit Slotmap() { clear(); }

    [[nodiscard]] std::size_t size()      const noexcept { return size_; }
    [[nodiscard]] std::size_t capacity()  const noexcept { return Capacity; }
    [[nodiscard]] key_type    push_back(RenderCMP const& newVal) {
        return push_back( RenderCMP{ newVal } ); 
    }
    [[nodiscard]] key_type    push_back(RenderCMP&& newVal) {
        auto reservedid = allocate();
        auto& slot = indices_[reservedid];
        //Move data
        data_[slot.id]  = std::move(newVal); 
        erase_[slot.id] = reservedid;
        //Key for the user
        auto key { slot };
        key.id = reservedid;
        
        return key;
    }
    bool clear() noexcept { freelist_init(); size_ = 0; return true;}

    bool erase(key_type key) noexcept {
        if ( !is_valid(key) ){ return false;};
        //Erase
        free(key);
        return true;    
    }
    [[nodiscard]] bool is_valid(key_type key) const noexcept{
        if ( key.id >= Capacity || indices_[key.id].gen != key.gen ) {return false;}
        return true;
    }


    RenderCMP& operator[](key_type const& key) noexcept {
        assert(is_valid(key));
        auto dataID = indices_[key.id].id;
        return data_[dataID];
    }
    RenderCMP const& operator[](key_type const key) const noexcept {
        assert(is_valid(key));
        auto dataID = indices_[key.id].id;
        return data_[dataID];
    }

    std::array<RenderCMP, Capacity>& getData(){
        return data_;
    }
    
    auto getFreelist(){
        return freelist_;
    }

private:
    [[nodiscard]] std::uint32_t allocate() {
        if (size_ >= Capacity) throw std::runtime_error(" No space left in the slotmap");
        assert(freelist_ < Capacity);

        //Reserve
        auto slotid = freelist_;
        freelist_ = indices_[slotid].id; //freelist to first slot free
        //Init Slot
        auto& slot = indices_[slotid];
        slot.id = size_;
        slot.gen = generation_;
        //Update space and generation
        ++size_;
        ++generation_;

        return slotid;
    }
    void free(key_type key) noexcept {
        assert(is_valid(key)); // if here the key is not valid , bad......
        
        auto& slot = indices_[key.id];
        auto dataid = slot.id; //Save id of data slot to check if it is last or not
        //Update freelist
        slot.id = freelist_;
        slot.gen = generation_;
        freelist_ = key.id;
        //Copy data to free slot???
        if ( dataid != size_ - 1 ){
            //data slot is not last, copy last here
            data_[dataid]   = data_[size_ - 1];
            erase_[dataid]  = erase_[size_ - 1];
            indices_[erase_[dataid]].id = dataid;
        }
        //Update size
        --size_;
        ++generation_;
    }
    void freelist_init() noexcept {
        for(std::uint32_t i{}; i < indices_.size(); ++i){
            indices_[i].id = i+1;
        }
        freelist_ = 0;
    }

    std::uint32_t                                size_{};
    std::uint32_t                                freelist_{};
    std::uint32_t                                generation_{};
    std::array<  key_type, Capacity >            indices_{};
    std::array<std::uint32_t, Capacity >         erase_{};
    std::array<RenderCMP, Capacity >             data_{};
};  

