////////////////////////////////////////////////////////////////////////////////
// Filename: water.fx
// http://www.rastertek.com/tertut16.html Used for Reference.
////////////////////////////////////////////////////////////////////////////////


/////////////
// GLOBALS //
/////////////
matrix inverseViewMatrix;
matrix inverseTranposeMatrix;
matrix worldMatrix;
matrix viewMatrix;
matrix projectionMatrix;
matrix reflectionMatrix;
Texture2D reflectionTexture;
Texture2D refractionTexture;
Texture2D normalTexture;
TextureCube skyboxTexture; 
float waterTranslation;
float reflectRefractScale;
float3 cameraPosition;

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
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
	float4 reflectionPosition : TEXCOORD1;
    float4 refractionPosition : TEXCOORD2;
	float3 texCoord : TEXCOORD3;
	
	float3 pos_eye: TEXCOORD4;
};


////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType WaterVertexShader(VertexInputType input)
{
    PixelInputType output;
    matrix reflectProjectWorld;
	matrix viewProjectWorld;
	
    
	// Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;

	// Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);

	//V-M position
	matrix normalMatrix = mul(viewMatrix, worldMatrix);
	output.pos_eye = input.position.xyz - cameraPosition;

    output.position = mul(output.position, projectionMatrix);

	// Store the texture coordinates for the pixel shader.
    output.tex = input.tex;
    
	// Create the reflection projection world matrix.
    reflectProjectWorld = mul(reflectionMatrix, projectionMatrix);
    reflectProjectWorld = mul(worldMatrix, reflectProjectWorld);

	// Calculate the input position against the reflectProjectWorld matrix.
    output.reflectionPosition = mul(input.position, reflectProjectWorld);

	// Create the view projection world matrix for refraction.
    viewProjectWorld = mul(viewMatrix, projectionMatrix);
    viewProjectWorld = mul(worldMatrix, viewProjectWorld);
   
	// Calculate the input position against the viewProjectWorld matrix.
    output.refractionPosition = mul(input.position, viewProjectWorld);


	return output;
}



////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 WaterPixelShader(PixelInputType input) : SV_Target
{
	float2 reflectTexCoord;
	float2 refractTexCoord;
	float4 normalMap;
	float3 normal;
	float4 reflectionColor;
	float4 refractionColor;
	float4 color;
	
	// Calculate the projected reflection texture coordinates.
    reflectTexCoord.x = input.reflectionPosition.x / input.reflectionPosition.w / 2.0f + 0.5f;
    reflectTexCoord.y = -input.reflectionPosition.y / input.reflectionPosition.w / 2.0f + 0.5f;
	
	// Calculate the projected refraction texture coordinates.
    refractTexCoord.x = input.refractionPosition.x / input.refractionPosition.w / 2.0f + 0.5f;
    refractTexCoord.y = -input.refractionPosition.y / input.refractionPosition.w / 2.0f + 0.5f;

	// Sample the normal from the normal map texture.
	normalMap = normalTexture.Sample(SampleType, input.tex);

	// Expand the range of the normal from (0,1) to (-1,+1).
	normal = (normalMap.xyz * 2.0f) - 1.0f;
	
	// Move the position the water normal is sampled from to simulate moving water.	
	normal.y += waterTranslation;

	float3 normal1 = normalize(normal);

	////Reflection stuff
	
	//reflection coord
	input.texCoord = mul(inverseTranposeMatrix,float4(normal1, 0.0)).xyz;

	float4 refNormal = (normal1, 0);
	matrix normalMatrix = mul(viewMatrix, worldMatrix);

	float3 n_eye = mul(normalMatrix, refNormal).xyz;
	float3 pos_eye = input.pos_eye;

	float reflection_contribution = 0.50;
	float3 incident_eye = normalize(-pos_eye);
	float3 nm = normalize(n_eye);
	float3 reflected = reflect(incident_eye, normal1);
	reflected = normalize(reflected);
	reflected = mul(inverseViewMatrix, float4(reflected, 0));


	// Re-position the texture coordinate sampling position by the normal map value to simulate the rippling wave effect.
	reflectTexCoord = reflectTexCoord + (normal.xy * reflectRefractScale);
	refractTexCoord = refractTexCoord + (normal.xy * reflectRefractScale);

	// Sample the texture pixels from the textures using the updated texture coordinates.
    //reflectionColor = reflectionTexture.Sample(SampleType, reflectTexCoord);
    refractionColor = refractionTexture.Sample(SampleType, refractTexCoord);
	reflectionColor = skyboxTexture.Sample(SampleType, reflected);


	// Combine the reflection and refraction results for the final color.
	color = lerp(reflectionColor, refractionColor, 0.6f);
	//return reflectionColor;0
	//return color;
	return color + float4(0,77/255.0, 1 , 1) * 0.1;
}

float3 relfect(float3 v1, float3 n)
{
	//reflection direction calculated as I - 2.0 * dot(N, I) * N.
	return v1 - 2 * dot(v1,n) * v1;
}

////////////////////////////////////////////////////////////////////////////////
// Technique
////////////////////////////////////////////////////////////////////////////////
technique10 WaterTechnique
{
    pass pass0
    {
        SetVertexShader(CompileShader(vs_4_0, WaterVertexShader()));
        SetPixelShader(CompileShader(ps_4_0, WaterPixelShader()));
        SetGeometryShader(NULL);
    }
}