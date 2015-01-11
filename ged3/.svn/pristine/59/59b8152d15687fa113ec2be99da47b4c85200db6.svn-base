////////////////////////////////////////////////////////////////////////////////
// Filename: Basic.fx 
// http://rastertek.com/dx10tut10.html for reference
// To create Phong Shading effect
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
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
	float3 instancePosition : TESTCOORD1;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
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

    input.position.x += input.instancePosition.x;
    input.position.y += input.instancePosition.y;
    input.position.z += input.instancePosition.z;

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

    // Calculate tangent vector
    output.tangent = mul(input.tangent, (float3x3)worldMatrix);
    output.tangent = normalize(output.tangent);

    // Calculate binormal vector
    output.binormal = mul(input.binormal, (float3x3)worldMatrix);
    output.binormal = normalize(output.binormal);

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
	// Declare all local variables within the pixel shader

 	float4 color;
	float4 textureColor;
	float3 lightDir;
    float lightIntensity;
 	float4 specularIntensity;
	float3 reflection;
   	float4 specular;

    // Sample the pixel color from the texture using the sampler at this texture coordinate location.
    textureColor = shaderTexture.Sample(SampleType, input.tex);

    // Set the default output color to the ambient light value for all pixels.
    color = ambientColor;

    // Initialize the specular color.
    specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

    // Invert the light direction for calculations.
    lightDir = -lightDirection;

    // Calculate the amount of light on this pixel.
    lightIntensity = saturate(dot(input.normal, lightDir));
	
    if(lightIntensity > 0.0f)
    {
        // Determine the final diffuse color based on the diffuse color and the amount of light intensity.
        color += (diffuseColor * lightIntensity);

        // Saturate the ambient and diffuse color.
        color = saturate(color);

		 // Calculate the reflection vector based on the light intensity, normal vector, and light direction.
        reflection = normalize(2 * lightIntensity * input.normal - lightDir); 
        // Determine the amount of specular light based on the reflection vector, viewing direction, and specular power.
        specular = pow(saturate(dot(reflection, input.viewDirection)), specularPower);
    }
	// Multiply the texture pixel and the input color to get the textured result.
    color = color * textureColor;
	// Add the specular component last to the output color.
    color = saturate(color + specular);

	//Shadow
	color *= Shadowing(input.normal, input.viewDirection,	input.lightViewPosition,	input.lightPos);
	
	return color;
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