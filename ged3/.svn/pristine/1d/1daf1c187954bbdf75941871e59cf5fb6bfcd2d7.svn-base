////////////////////////////////////////////////////////////////////////////////
// Filename: TextureOnly.fx 
// Only render texture, and shadow
////////////////////////////////////////////////////////////////////////////////
#include "Shadow/shadow.fx"

/////////////
// GLOBALS //
/////////////
matrix worldMatrix;
matrix viewMatrix;
matrix projectionMatrix;

Texture2D shaderTexture;

float3 lightDirection;

float4 ambientColor;
float ambientIntensity = 2.0;

float4 diffuseColor;
float4 specularColor;
float specularPower;

///////////////////
// SAMPLE STATES //
///////////////////
SamplerState SampleType
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};


//////////////
// TYPEDEFS //
//////////////
struct VertexInputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	//shadow att
    float3 viewDirection : TEXCOORD1;
	float4 lightViewPosition : TEXCOORD2;
	float3 lightPos : TEXCOORD3;
};

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType LightVertexShader(VertexInputType input)
{

    PixelInputType output;
    float4 worldPosition;
    
    // Change the position vector to be 4 units for proper matrix calculations
    input.position.w = 1.0f;

    // Calculate the position of the vertex against the world, view, and projection matrices
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);

    // Store the texture coordinates
    output.tex = input.tex;
	
	    // Calculate the normal vector
    output.normal = mul(input.normal, (float3x3)worldMatrix);
    output.normal = normalize(output.normal);

	// Calculate the position of the vertex in the world
    worldPosition = mul(input.position, worldMatrix);
	//Shadow thigns
    // Determine the viewing direction
    output.viewDirection = cameraPosition.xyz - worldPosition.xyz;
    output.viewDirection = normalize(output.viewDirection);


	// Calculate the position of the vertice as viewed by the light source.
    output.lightViewPosition = mul(input.position, worldMatrix);
    output.lightViewPosition = mul(output.lightViewPosition, lightViewMatrix);
    output.lightViewPosition = mul(output.lightViewPosition, lightProjectionMatrix);

    // Determine the light position based on the position of the light and the position of the vertex in the world.
    output.lightPos = lightPosition.xyz - worldPosition.xyz;

    // Normalize the light position vector.
    output.lightPos = normalize(output.lightPos);

    return output;
}


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 LightPixelShader(PixelInputType input) : SV_Target
{

    // Sample the pixel color from the texture using the sampler at this texture coordinate location.

	return shaderTexture.Sample(SampleType, input.tex) 
		* Shadowing(input.normal, input.viewDirection,	input.lightViewPosition,	input.lightPos);
	//return depthMapTexture.Sample(SampleType, input.tex) ;
	//return float4(input.lightPos,0);
	//return float4(input.normal,0);
	//return input.lightViewPosition;
}


////////////////////////////////////////////////////////////////////////////////
// Technique
////////////////////////////////////////////////////////////////////////////////
technique10 LightTechnique
{
    pass pass0
    {
        SetVertexShader(CompileShader(vs_4_0, LightVertexShader()));
        SetPixelShader(CompileShader(ps_4_0, LightPixelShader()));
		SetGeometryShader(NULL);
    }
}