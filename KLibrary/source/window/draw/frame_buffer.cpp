#include "window/draw/frame_buffer.h"


kl::frame_buffer::frame_buffer(const int2& size)
{
    resize(size);
}

kl::frame_buffer::~frame_buffer()
{}

kl::int2 kl::frame_buffer::size() const
{
    return buffers_[0].size();
}

void kl::frame_buffer::resize(const kl::int2& new_size)
{
    for (auto& buffer : buffers_) {
        buffer.resize(new_size);
    }
}

kl::image* kl::frame_buffer::back_buffer()
{
    return !first_is_front ? (buffers_ + 0) : (buffers_ + 1);
}

const kl::image& kl::frame_buffer::front_buffer() const
{
    return first_is_front ? buffers_[0] : buffers_[1];
}

void kl::frame_buffer::swap()
{
    first_is_front = !first_is_front;
}
