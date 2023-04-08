// Vertex shader
cbuffer vs_cb : register(b0)
{
    float4 position_data; // (x_index, y_index, none, none)
    float4 viewport_data; // (width, height, aspect, none)
}

struct vs_out
{
    float4 position : SV_Position;
    float2 textur : VS_Texture;
};

vs_out v_shader(const float3 position : KL_Position, const float2 textur : KL_Texture)
{
    float2 altered_position = (position.xy + 1) * 0.0625;
    altered_position = altered_position * 2 - 1;
    altered_position += position_data.xy * 0.25;

    if (viewport_data.y > viewport_data.x) {
        altered_position.y *= viewport_data.z;
    }
    else {
        altered_position.x /= viewport_data.z;
    }

    vs_out data;
    data.position = float4(altered_position, 0.5, 1);
    data.textur = textur;
    return data;
}

// Pixel shader
cbuffer ps_cb : register(b0)
{
    float4 square_color;
}

SamplerState texture_sampler : register(s0);
Texture2D      piece_texture : register(t0);

float4 p_shader(const vs_out data) : SV_Target
{
    const float4 texture_color = piece_texture.Sample(texture_sampler, data.textur);
    const float3 final_color = lerp(square_color.xyz, texture_color.xyz, texture_color.w);
    return float4(final_color, 1);
}
