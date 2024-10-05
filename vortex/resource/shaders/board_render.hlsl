// Vertex shader
cbuffer vs_cb : register(b0)
{
    float4   position_data; // (x_index, y_index, none, none)
    float4   viewport_data; // (width, height, aspect, none)
    float4 offset_position; // (x, y, exists?, none)
}

struct vs_out
{
    float4 position : SV_Position;
    float2 textur : VS_Texture;
};

vs_out v_shader(float3 position : KL_Position, const float2 textur : KL_Texture)
{
    // Resizing
    if (offset_position.z) {
        position *= 1.25;
    }

    // Moving
    float2 altered_position = (position.xy + 1) * 0.0625;
    altered_position = altered_position * 2 - 1;
    altered_position += (offset_position.z) ? (offset_position.xy + 0.875) : (position_data.xy * 0.25);

    // Apply aspect
    if (viewport_data.y > viewport_data.x) {
        altered_position.y *= viewport_data.z;
    }
    else {
        altered_position.x /= viewport_data.z;
    }

    // Save data
    vs_out data;
    data.position = float4(altered_position, 0.5, 1);
    data.textur = textur;
    return data;
}

// Pixel shader
cbuffer ps_cb : register(b0)
{
    float4 square_color; // (r, g, b, render_type)
}

SamplerState texture_sampler : register(s0);
Texture2D      piece_texture : register(t0);

float4 p_shader(const vs_out data) : SV_Target
{
    // Only square color
    if (square_color.w == 0) {
        return float4(square_color.xyz, 1);
    }
    
    // Only piece texture
    if (square_color.w == 1) {
        return piece_texture.Sample(texture_sampler, data.textur);
    }

    // Both square color and piece texture
    const float4 correct_square_color = float4(square_color.xyz, 1);
    const float4 texture_color = piece_texture.Sample(texture_sampler, data.textur);
    return lerp(correct_square_color, texture_color, texture_color.w);
}
