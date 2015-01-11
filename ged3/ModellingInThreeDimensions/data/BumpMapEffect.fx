////////////////////////////////////////////////////////////////////////////////
// Filename: BumpMapEffect.fx
// http://rastertek.com/dx10tut20.html
// To create basic effect of roughness on flat surface
////////////////////////////////////////////////////////////////////////////////


#include "Shadow/shadow.fx"
/////////////
// GLOBALS //
/////////////
matrix worldMatrix;
matrix viewMatrix;
matrix projectionMatrix;

Texture2D shaderTexture[3];

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
    float3 instancePosition : TESTCOORD1;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
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
	output.binormal = cross(output.normal, output.tangent);

    // Calculate the position of the vertex in the world
    worldPosition = mul(input.position, worldMatrix);

    // Determine the viewing direction
    output.viewDirection = cameraPosition.xyz - worldPosition.xyz;
    output.viewDirection = normalize(output.viewDirection);
	
	//Shadow thigns
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
        float3 bumpMap;
	float3 bumpNormal;
	float3 lightDir;
        float lightIntensity;
 	float4 specularIntensity;
    	float3 reflection;
   	float4 specular;

	// Sample the texture color from the first texture
    textureColor = shaderTexture[0].Sample(SampleType, input.tex);

	// Calculate the bump normal by sampling the color from the second texture
	bumpMap = shaderTexture[1].Sample(SampleType, input.tex).rgb;
	bumpMap = (bumpMap*2.0f)-1.0f;	// Converts from value between 0 and 1 to a value between -1 and 1.

	bumpNormal = input.normal + bumpMap.x*input.tangent + bumpMap.y*input.binormal;
	bumpNormal = normalize(bumpNormal);
	
	// Adds core ambient light to all pixels
	color = ambientColor * ambientIntensity;

	// Invert the light direction for calculations
    	lightDir = -lightDirection;
	// Calculate the diffuse light value with relation to the bump normal
    	lightIntensity = saturate(dot(bumpNormal, lightDir));
	lightIntensity *= 2;
   	color += saturate(diffuseColor * lightIntensity);

	if(lightIntensity > 0.0f)
    	{
	
        	// Sample the intensity of the specular light from the third texture
        	specularIntensity = shaderTexture[2].Sample(SampleType, input.tex);

        	// Calculate the reflection vector and use to determine the specular color
        	reflection = normalize(2 * lightIntensity * bumpNormal - lightDir); 
        	specular = pow(saturate(dot(reflection, input.viewDirection)), specularPower);
        	specular = specular * specularIntensity;
		
        	color = saturate(color + specular);
    	}
	//Shadow
	//color *= Shadowing(input.normal, input.viewDirection,	input.lightViewPosition,	input.lightPos);

	return color * textureColor;
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