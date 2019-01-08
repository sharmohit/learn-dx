cbuffer ModelViewProjectionConstantBuffer : register(b0)
{
	matrix World;       // world matrix for object
	matrix View;        // view matrix
	matrix Projection;  // projection matrix
};

struct VS_INPUT
{
	float3 vPos   : POSITION;
	float3 vColor : COLOR0;
};

struct VS_OUTPUT
{
	float4 Position : SV_POSITION; // Vertex shaders must output SV_POSITION
	float4 Color    : COLOR0;
};

VS_OUTPUT main(VS_INPUT input) // main is the default function name
{
	VS_OUTPUT Output;

	float4 pos = float4(input.vPos, 1.0f);

		// Transform the position from object space to homogeneous projection space
		pos = mul(pos, World);
	pos = mul(pos, View);
	pos = mul(pos, Projection);
	Output.Position = pos;

	// Just pass through the color data
	Output.Color = float4(input.vColor, 1.0f);

	return Output;
}