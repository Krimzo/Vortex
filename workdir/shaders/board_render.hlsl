struct VS_OUT
{
    float4 position : SV_Position;
    float2 uv : VS_UV;
};

float4 SQUARE_COLOR;
float2 VIEWPORT_SIZE;
float2 PIECE_INDEX;
float2 OFFSET_POS;
float PIECE_EXISTS;
float ASPECT_RATIO;

Texture2D PIECE_TEXTURE : register(t0);

SamplerState PIECE_SAMPLER : register(s0);

VS_OUT v_shader(float3 position : KL_Position, float2 uv : KL_UV)
{
    if (PIECE_EXISTS)
    {
        position *= 1.25;
    }
    
    float2 altered_position = (position.xy + 1.0f) * 0.0625f;
    altered_position = altered_position * 2.0f - 1.0f;
    altered_position += PIECE_EXISTS ? (OFFSET_POS + 0.875f) : (PIECE_INDEX * 0.25f);

    if (VIEWPORT_SIZE.y > VIEWPORT_SIZE.x)
    {
        altered_position.y *= ASPECT_RATIO;
    }
    else {
        altered_position.x /= ASPECT_RATIO;
    }

    VS_OUT data;
    data.position = float4(altered_position, 0.5f, 1.0f);
    data.uv = uv;
    return data;
}

float4 p_shader(VS_OUT data) : SV_Target0
{
    if (SQUARE_COLOR.w == 0.0f)
        return float4(SQUARE_COLOR.xyz, 1.0f);

    if (SQUARE_COLOR.w == 1.0f)
        return PIECE_TEXTURE.Sample(PIECE_SAMPLER, data.uv);

    float4 square_color = float4(SQUARE_COLOR.xyz, 1.0f);
    float4 texture_color = PIECE_TEXTURE.Sample(PIECE_SAMPLER, data.uv);
    return lerp(square_color, texture_color, texture_color.w);
}
