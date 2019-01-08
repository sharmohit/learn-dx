cbuffer ModelViewProjectionConstantBuffer : register(b0)
{
	matrix World;       // world matrix for object
	matrix View;        // view matrix
	matrix Projection;  // projection matrix
};

struct VS_INPUT
{
	float3 position   : POSITION;
	float2 tex : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 position : SV_POSITION; // Vertex shaders must output SV_POSITION
	float2 tex   : TEXCOORD0;
};

VS_OUTPUT main(VS_INPUT input) // main is the default function name
{
	VS_OUTPUT output;

	float4 pos = float4(input.position, 1.0f);

		// Transform the position from object space to homogeneous projection space
		pos = mul(pos, World);
	pos = mul(pos, View);
	pos = mul(pos, Projection);
	output.position = pos;

	// Just pass through the texcoord
	output.tex = input.tex;

	return output;
}