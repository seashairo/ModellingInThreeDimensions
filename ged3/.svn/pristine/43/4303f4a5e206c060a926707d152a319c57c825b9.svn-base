////////////////////////////////////////////////////////////////////////////////
// Filename: terrain.fx 
// Phong Shading effect
// http://www.rastertek.com/tertut02.html Used for reference.
// http://www.rastertek.com/tertut14.html Used for reference.
////////////////////////////////////////////////////////////////////////////////
#include "../Shadow/shadow.fx"

/////////////
// GLOBALS //
/////////////
matrix worldMatrix;
matrix viewMatrix;
matrix projectionMatrix;

Texture2D shaderTexture;
Texture2D grassTexture;
Texture2D slopeTexture;
Texture2D rockTexture;

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
	float3 lightDir;
	float lightIntensity;
	float blendAmount;
	float4 grassColor;
   	 float4 slopeColor;
	float4 rockColor;
	float4 textureColor;
	float4 color;
	float gradient;

    // Sample the grass color from the texture using the sampler at this texture coordinate location.
    grassColor = grassTexture.Sample(SampleType, input.tex);

    // Sample the slope color from the texture using the sampler at this texture coordinate location.
    slopeColor = slopeTexture.Sample(SampleType, input.tex);

    // Sample the rock color from the texture using the sampler at this texture coordinate location.
    rockColor = rockTexture.Sample(SampleType, input.tex);	

    // Set the default output color to the ambient light value for all pixels.
    color = ambientColor;

    // Calculate the gradient of this point.
    gradient = 1.0f - input.normal.y;
	
    // Determine which texture to use based on height.
    if(gradient < 0.2)
    {
        blendAmount = gradient / 0.2f;
        textureColor = lerp(grassColor, slopeColor, blendAmount);
    }
	
    if((gradient < 0.7) && (gradient >= 0.2f))
    {
        blendAmount = (gradient - 0.2f) * (1.0f / (0.7f - 0.2f));
        textureColor = lerp(slopeColor, rockColor, blendAmount);
    }
	
    if(gradient >= 0.7) 
    {
        textureColor = rockColor;
	}

	/*
    // Invert the light direction for calculations.
    lightDir = -lightDirection;

    // Calculate the amount of light on this pixel.
    lightIntensity = saturate(dot(input.normal, lightDir));
	
	if(lightIntensity > 0.0f)
    {
        // Determine the final diffuse color based on the diffuse color and the amount of light intensity.
        color += (diffuseColor * lightIntensity);
    }

    // Saturate the final light color.
    color = saturate(color);
	/
    // Multiply the texture pixel and the final diffuse color to get the final pixel color result.
	color = color * textureColor;

	*/
	color = textureColor;
	//input.normal *= -1;
	//Shadow
	color *= Shadowing(input.normal, input.viewDirection,	input.lightViewPosition,	input.lightPos);

	return color;
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