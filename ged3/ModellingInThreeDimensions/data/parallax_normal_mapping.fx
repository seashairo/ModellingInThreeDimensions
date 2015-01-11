////////////////////////////////////////////////////////////////////////////////
// Filename: light.fx
////////////////////////////////////////////////////////////////////////////////


/////////////
// GLOBALS //
/////////////
matrix worldMatrix;
matrix viewMatrix;
matrix projectionMatrix;
matrix worldInverseTransposeMatrix;
matrix worldViewProjectionMatrix;

Texture2D shaderTexture[3];

float3 lightDirection;

float4 ambientColor;
float ambientIntensity = 4.0;

float4 diffuseColor;

float3 cameraPosition;
float4 specularColor;
float specularPower;

float2 scalebias;

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
	float3 halfVector : TEXCOORD2;
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

    worldPosition = mul(input.position, worldMatrix);

    // Determine the viewing direction
    output.viewDirection = cameraPosition.xyz - worldPosition.xyz;
    output.viewDirection = normalize(output.viewDirection);
	float3 halfVector = normalize(normalize(lightDirection) + output.viewDirection);
	
	float3 n = mul(output.normal, (float3x3)worldInverseTransposeMatrix);
	float3 t = mul(output.tangent.xyz, (float3x3)worldInverseTransposeMatrix);
	float3 b = cross(n, t);
	float3x3 tbnMatrix = float3x3(t.x, b.x, n.x,
	                              t.y, b.y, n.y,
	                              t.z, b.z, n.z);

	output.halfVector = mul(halfVector, tbnMatrix);

    return output;
}


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 LightPixelShader(PixelInputType input) : SV_Target
{
	// Declare all local variables within the pixel shader
	float2 texcoord;
    float3 h = normalize(input.halfVector);
    float height = shaderTexture[2].Sample(SampleType, input.tex).r;
    height = height * scalebias.x + scalebias.y;
    texcoord = input.tex + (height * h.xy);


    //float3 l = normalize(input.viewDirection);
	float3 l = normalize(lightDirection);
    float3 n = normalize(shaderTexture[1].Sample(SampleType, texcoord).rgb * 2.0f - 1.0f);
    
    float ndotl = saturate(dot(n, l));
    float ndoth = saturate(dot(n, h));
    float power = (ndotl == 0.0f) ? 0.0f : pow(ndoth, specularPower);
	float4 color = (diffuseColor * ndotl) + (specularColor * power) + (ambientColor * ambientIntensity);
	//return shaderTexture[0].Sample(SampleType, texcoord);
	//return color;
	return color * shaderTexture[0].Sample(SampleType, texcoord);
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