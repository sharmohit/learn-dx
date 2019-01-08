Texture2D Texture : register(t0);
SamplerState SampleType : register(s0);

struct PS_INPUT
{
	float4 Position : SV_POSITION;
	float2 Tex    : TEXCOORD0;
};

float4 main(PS_INPUT input) : SV_TARGET
{
	float4 texColor;
	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
	texColor = Texture.Sample(SampleType, input.Tex);
	return texColor;
}