#include "memory_helper.h"


uintptr_t internal_align_address_forward(uintptr_t address) {
    uintptr_t nearestAlignedFactor = address / (uintptr_t)ALIGNMENT;
    uintptr_t nearestAlignedAddress = nearestAlignedFactor * (uintptr_t)ALIGNMENT;
    //Lower, but aligned address

    if(nearestAlignedAddress == address) {
        return address;
    }

    uintptr_t requiredAlignment = (uintptr_t)ALIGNMENT - (address - nearestAlignedAddress);

    return address + requiredAlignment;
}

uintptr_t internal_align_address_backward(uintptr_t address) {
    uintptr_t nearestAlignedFactor = address / (uintptr_t)ALIGNMENT;
    uintptr_t nearestAlignedAddress = nearestAlignedFactor * (uintptr_t)ALIGNMENT;
    //Lower, but aligned address

    return address;
}


void *internal_get_node_end(Node *node) {
    void *end = node + sizeof(Node);
    return end;
}


Node *internal_find_previous_block(uintptr_t ptr) {
    uintptr_t header = ptr - sizeof(Node);

    uint32_t previousFooter = internal_align_address_backward(header - sizeof(uint32_t));
}


uintptr_t internal_find_next_block(uintptr_t ptr) {

}

