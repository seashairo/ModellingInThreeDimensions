////////////////////////////////////////////////////////////////////////////////
// Filename: reflection.fx
// http://www.rastertek.com/terdx10tut16.html Used for reference.
////////////////////////////////////////////////////////////////////////////////


/////////////
// GLOBALS //
/////////////
matrix worldMatrix;
matrix viewMatrix;
matrix projectionMatrix;
Texture2D colorTexture;
Texture2D normalTexture;
float4 lightDiffuseColor;
float3 lightDirection;
float colorTextureBrightness;
float4 clipPlane;


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
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
	float4 color : COLOR;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
   	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
	float4 color : COLOR;
   	float clip : SV_ClipDistance0;
};


////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType ReflectionVertexShader(VertexInputType input)
{
    PixelInputType output;
    

	// Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;

	// Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    
	// Store the texture coordinates for the pixel shader.
	output.tex = input.tex;
    
    // Calculate the normal vector against the world matrix only and then normalize the final value.
    output.normal = mul(input.normal, (float3x3)worldMatrix);
    output.normal = normalize(output.normal);

	// Calculate the tangent vector against the world matrix only and then normalize the final value.
    output.tangent = mul(input.tangent, (float3x3)worldMatrix);
    output.tangent = normalize(output.tangent);

    // Calculate the binormal vector against the world matrix only and then normalize the final value.
    output.binormal = mul(input.binormal, (float3x3)worldMatrix);
    output.binormal = normalize(output.binormal);

	// Send the color map color into the pixel shader.	
    output.color = input.color;

	// Set the clipping plane.
    output.clip = dot(mul(input.position, worldMatrix), clipPlane);

    return output;
}


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 ReflectionPixelShader(PixelInputType input) : SV_Target
{
	float3 lightDir;
	float4 textureColor;
	float4 bumpMap;
    float3 bumpNormal;
    float lightIntensity;
    float4 color;


    // Invert the light direction for calculations.
    lightDir = -lightDirection;

    // Sample the color texture.
    textureColor = colorTexture.Sample(SampleType, input.tex);

	// Combine the color map value into the texture color.
	textureColor = saturate(input.color * textureColor * colorTextureBrightness);

	// Calculate the bump map using the normal map.
	bumpMap = normalTexture.Sample(SampleType, input.tex);
	bumpMap = (bumpMap * 2.0f) - 1.0f;
	bumpNormal = input.normal + bumpMap.x * input.tangent + bumpMap.y * input.binormal;
	bumpNormal = normalize(bumpNormal);
    lightIntensity = saturate(dot(bumpNormal, lightDir));
    
	// Calculate the first bump mapped pixel color.
	color = saturate(lightDiffuseColor * lightIntensity);
    color = color * textureColor;

	return color;
}


////////////////////////////////////////////////////////////////////////////////
// Technique
////////////////////////////////////////////////////////////////////////////////
technique10 ReflectionTechnique
{
    pass pass0
    {
        SetVertexShader(CompileShader(vs_4_0, ReflectionVertexShader()));
        SetPixelShader(CompileShader(ps_4_0, ReflectionPixelShader()));
        SetGeometryShader(NULL);
    }
}