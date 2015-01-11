////////////////////////////////////////////////////////////////////////////////
// Filename: Skybox.fx 
// Create skybox
////////////////////////////////////////////////////////////////////////////////


/////////////
// GLOBALS //
/////////////
matrix worldMatrix;
matrix viewMatrix;
matrix projectionMatrix;

TextureCube gSkyMap;

///////////////////
// SAMPLE STATES //
///////////////////
SamplerState TriLinearSample
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

struct VertexInputType
{
    float4 position : POSITION;
    float3 tex : TEXCOORD0;
    float3 normal : NORMAL;
};


struct SKYMAP_VS_OUTPUT	//output structure for skymap vertex shader
{
    float4 position : SV_POSITION;
	float3 texCoord : TEXCOORD;
};

SKYMAP_VS_OUTPUT SKYMAP_VS(VertexInputType input)
{
	SKYMAP_VS_OUTPUT output = (SKYMAP_VS_OUTPUT)0;

	// Change the position vector to be 4 units for proper matrix calculations
    input.position.w = 1.0f;

    // Calculate the position of the vertex against the world, view, and projection matrices
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);

	//true version
	output.texCoord = input.position.xyz;

	//just for now
	/*output.texCoord.xy = input.tex;
	output.texCoord.z = 1;*/

    return output;		//send color and position to pixel shader
}

float4 SKYMAP_PS(SKYMAP_VS_OUTPUT input) : SV_Target
{
	//return float4(0,0,0,0);
	return gSkyMap.Sample(TriLinearSample, input.texCoord);
}

technique10 SkyTech
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, SKYMAP_VS() ) );
        SetPixelShader( CompileShader( ps_4_0, SKYMAP_PS() ) );
    }
}
