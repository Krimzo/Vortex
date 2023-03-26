#pragma once

#include "media/media.h"


namespace kl {
    class frame_buffer
    {
        bool first_is_front = true;
        image buffers_[2] = {};

    public:
        frame_buffer(const int2& size);
        virtual ~frame_buffer();

        frame_buffer(const frame_buffer&) = delete;
        frame_buffer(const frame_buffer&&) = delete;

        void operator=(const frame_buffer&) = delete;
        void operator=(const frame_buffer&&) = delete;

        int2 size() const;
        void resize(const kl::int2& new_size);

        image* back_buffer();
        const image& front_buffer() const;

        void swap();
    };
}
