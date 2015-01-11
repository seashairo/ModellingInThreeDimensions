////////////////////////////////////////////////////////////////////////////////
// Filename: foliage.fx
// http://www.rastertek.com/terdx10tut19.html Used For Reference.
////////////////////////////////////////////////////////////////////////////////


/////////////
// GLOBALS //
/////////////
matrix viewMatrix;
matrix projectionMatrix;
Texture2D shaderTexture;


///////////////////
// SAMPLE STATES //
///////////////////
SamplerState SampleType
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Clamp;
    AddressV = Clamp;
};


//////////////
// TYPEDEFS //
//////////////
struct VertexInputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
	row_major matrix instanceWorld : WORLD;
	float3 instanceColor : TEXCOORD1;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
	float3 foliageColor : TEXCOORD1;
};


////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType FoliageVertexShader(VertexInputType input)
{
    PixelInputType output;
    
    
	// Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;
	
	// Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(input.position, input.instanceWorld);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    
	// Store the texture coordinates for the pixel shader.
    output.tex = input.tex;
    
	// Send the instanced foliage color into the pixel shader.
	output.foliageColor = input.instanceColor;

	return output;
}


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 FoliagePixelShader(PixelInputType input) : SV_Target
{
	float4 textureColor;
	float4 color;


	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
	textureColor = shaderTexture.Sample(SampleType, input.tex);

	// Combine the texture and the foliage color.
	color = textureColor * float4(input.foliageColor, 1.0f);

	// Saturate the final color result.
	color = saturate(color);

    return color;
}


////////////////////////////////////////////////////////////////////////////////
// Technique
////////////////////////////////////////////////////////////////////////////////
technique10 FoliageTechnique
{
    pass pass0
    {
        SetVertexShader(CompileShader(vs_4_0, FoliageVertexShader()));
        SetPixelShader(CompileShader(ps_4_0, FoliagePixelShader()));
        SetGeometryShader(NULL);
    }
}