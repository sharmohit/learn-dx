struct PS_INPUT
{
	float4 Position : SV_POSITION;  // interpolated vertex position (system value)
	float4 Color    : COLOR0;       // interpolated diffuse color
};

float4 main(PS_INPUT In) : SV_TARGET
{
return In.Color;
}