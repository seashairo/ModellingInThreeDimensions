////////////////////////////////////////////////////////////////////////////////
// Filename: Parallax_Mapping.fx
// http://developer.download.nvidia.com/SDK/10.5/direct3d/screenshots/samples/ParallaxMapping.html
////////////////////////////////////////////////////////////////////////////////
#include "Shadow/shadow.fx"
#define N_DOT_V_LERPING 
#define SELF_SHADOWING
//#define BINARY_SEARCH
#define OFFSET_SHADOW
/////////////
// GLOBALS //
/////////////
matrix worldMatrix;
matrix viewMatrix;
matrix projectionMatrix;
matrix worldInverseTransposeMatrix;
matrix worldViewProjectionMatrix; //this is viewProjection matrix, not MVP

Texture2D shaderTexture[3];

float3 lightDirection;

float4 ambientColor;
float ambientIntensity = 4.0;

float4 diffuseColor;

float4 specularColor;
float specularPower;

float2 g_TexScale = {4.0f, 20.0f};

//Add

static const float4 g_matDiffuse   = { 1.00f, 1.00f, 1.00f, 1.0f };
static const float4 g_matAmbient   = { 0.35f, 0.35f, 0.35f, 0.0f };
static const float4 g_matSpecular  = {  0.5f,  0.5f,  0.5f, 1.0f };

static const float  g_ShadowHardness = 0.75f;
static const float  g_Offset         = 0.01f;
static const float  g_ExtrudeScale   = 0.05f;

float  g_Sign            =   1.00f;
float  g_ExtrudeFin      =   0.15f;
float  g_ExtrudeAngle    =   0.01f;
float  g_CoarseSteps     =   8.00f;
float  g_DetailSteps     =   8.00f;
float  g_CoarseStepsMin  =   8.00f;
float  g_DetailStepsMin  =   8.00f;
float  g_CoarseStepsMax  =  24.00f;
float  g_DetailStepsMax  =  24.00f;
float  g_ParallaxClamp	 =   3.00f;


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
};

struct GS_INPUT
{
    float4 Position  : POSITION;
    float2 TexCoord  : TEXCOORD0;
    float3 Normal    : NORMAL;
    float3 Tangent   : TANGENT;
	float3 viewDirection: TEXCOORD1;
};


struct PixelInputType
{
    float4 Position  : SV_POSITION;
    float2 TexCoord  : TEXCOORD0;
    float3 Normal    : TEXCOORD1;
    float3 Tangent   : TEXCOORD2;
	float4 PosWS     : TEXCOORD3;
		//shadow att
    float3 viewDirection : TEXCOORD4;
	float4 lightViewPosition : TEXCOORD5;
	float3 lightPos : TEXCOORD6;
};

SamplerState  sClamp
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Clamp;
    AddressV = Clamp;
};

SamplerState sLinear
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Mirror;
	AddressV = Mirror;
};

RasterizerState DisableCulling
{
	FillMode = SOLID;
	CullMode = NONE;
};

float2 ParallaxVector(float3 ViewTS)
{
	float  ParallaxLength    = length   (ViewTS.xy) / (length(ViewTS.z) + g_Offset);
    float2 ParallaxDirection = normalize(ViewTS.xy);
    ParallaxDirection = ParallaxDirection * g_ExtrudeScale * min( ParallaxLength, g_ParallaxClamp );
    return ParallaxDirection;
}

float3 ToTangentSpace(float3 Normal, float3 Tangent, float3 Vector)
{
	float3 Bitangent = normalize(cross(Normal, Tangent));
	//float3 Bitangent = normalize(cross(Tangent, Normal));
    
    float3x3 TangentTransform = float3x3(Tangent, Bitangent, Normal);
    
    float3   VectorTS = mul(TangentTransform, Vector);

    return VectorTS;
}
float4 Lighting( float2 texCoord, float3 LightTS, float3 ViewTS, float Shadow, float mipLevel )
{
   float3 NormalTS = normalize( shaderTexture[1].SampleLevel( sLinear, texCoord, mipLevel).rgb * 2 - 1 );

   float4 BaseColor = shaderTexture[0].SampleLevel( sLinear, texCoord, mipLevel);
   
   //LightTS = float3( LightTS.x, LightTS.y, LightTS.z );

   float4 Diffuse = saturate( dot( NormalTS, LightTS )) * diffuseColor;
    
   float4 Specular = 0;

  //float3 ReflectionTS = normalize( 2 * dot( ViewTS, NormalTS ) * NormalTS - ViewTS );
  //float3 ReflectionTS = normalize( 2 * dot( LightTS, NormalTS ) * NormalTS - LightTS );
  float3 ReflectionTS = normalize( -reflect(ViewTS, NormalTS) );
       
  float RdotL = saturate( dot( ReflectionTS, LightTS ));
  Specular = saturate( pow( RdotL, 60 )) * specularColor;

   float4 FinalColor = ((ambientColor * ambientIntensity + Diffuse ) * BaseColor + Specular ); 
   
   return FinalColor;  
}   

float CalculateMipLevel(float2 texcoord)
{
    float2 dx = ddx( texcoord );
    float2 dy = ddy( texcoord );
   
    return log2( max( sqrt(dot(dx, dx)), sqrt(dot(dy, dy)) ) );
}

float TraceLinear(Texture2D Height, inout float2 CurrPoint, inout float CurrHeight, float2 tStep, float hStep, float mipLevel, float iSteps, inout float Intersected)
{
	float tHeight;
	for (float i = 0.0f; i < (int)iSteps; i++ )
    {
		// The trace will stop at the point before the actuall intersection with height field happens
	    tHeight = 1.0f - Height.SampleLevel( sLinear, CurrPoint - tStep, mipLevel ).x;

		if( (CurrHeight - hStep > tHeight) && (CurrHeight > 0) )
	    {
		    CurrHeight -= hStep;
		    CurrPoint  -= tStep;
	    }
	    else
	    {
		    Intersected = 1.0f;
		    i = iSteps;
	    }
    }
	return tHeight;
}

float TraceBinary(Texture2D Height, inout float2 CurrPoint, inout float CurrHeight, float2 tStep, float hStep, float mipLevel, float iSteps, float eps)
{
	// the intersection happens somewhere between [CurrPoint, CurrPoint - tStep]
	float2 pPrev = CurrPoint;            // the current point will be considered Previous
	float2 pNext = CurrPoint  - tStep;   // the point were intersection happens will be considered Next
	float  hPrev = CurrHeight;           
	float  hNext = CurrHeight - hStep;

	float tHeight = 0.0f;

	for (float i = 0.0f; i < (int)iSteps; i++ )
	{
		// the intersection happens somewhere between [pPrev, pNext]
		CurrHeight = (hNext + hPrev) * 0.5f; 
		CurrPoint  = (pNext + pPrev) * 0.5f;

		tHeight = 1.0f - Height.SampleLevel( sLinear, CurrPoint, mipLevel ).x;			
		float delta = CurrHeight - tHeight;
		
		if (abs(delta) > eps)
		{	        
			if ( CurrHeight > tHeight )
			{
				pPrev = CurrPoint;
				hPrev = CurrHeight;
			}
			else
			{
				pNext = CurrPoint;
				hNext = CurrHeight;
			}
		}
		else
		{ 
			i = iSteps;
		}
	}   

	CurrPoint  = (pPrev + pNext)  * 0.5f;
	CurrHeight = (hPrev + hNext) * 0.5f;

	return tHeight;
}

float TraceLight(Texture2D Height, float2 currPoint, float2 RayTS, float mipLevel, float iSteps)
{
	float Shadow = Height.SampleLevel( sLinear, currPoint, mipLevel ).x;
	
	float Scale = (iSteps - 1) / iSteps;	
	float Result = (shaderTexture[2].SampleLevel( sLinear, currPoint + RayTS * Scale, mipLevel ).x - Shadow + Scale ) * 0.58;

	for (float i = 2; i < iSteps; i++)
	{
		Scale = (iSteps - i) / iSteps;
		float Sh = (shaderTexture[2].SampleLevel( sLinear, currPoint + RayTS * Scale, mipLevel ).x - Shadow + Scale ) *  2 * (i - 1);
		Result = max(Result, Sh);
	}
	Result = Result * g_ShadowHardness + (1.0f - g_ShadowHardness);
	return Result * 0.6f;
}

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType LightVertexShader(VertexInputType input)
{
    PixelInputType output;
    float3 worldPosition; 
    
    // Store the texture coordinates
    output.TexCoord = input.tex.yx;

    // Calculate the normal vector
    //output.Normal = mul(float3(0,0,-1), (float3x3)worldMatrix);
	output.Normal = mul(input.normal, (float3x3)worldMatrix);

    // Calculate tangent vector
    //output.Tangent = mul(float3(0,1,0), (float3x3)worldMatrix);
	output.Tangent = mul(input.tangent, (float3x3)worldMatrix);

    worldPosition = mul(input.position, worldMatrix);;
	//worldPosition = mul(worldPosition, viewMatrix);;

	output.PosWS.xyz = worldPosition;
	output.PosWS.w = 1.0f;

	output.Position = mul(input.position, worldMatrix);
    output.Position = mul(output.Position, viewMatrix);
    output.Position = mul(output.Position, projectionMatrix);

	//Shadow thigns
    // Determine the viewing direction
    output.viewDirection = cameraPosition.xyz - worldPosition.xyz;

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


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Silhouette Clipping Section/////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GS_INPUT VSSilhouette( VertexInputType In )
{
    GS_INPUT Out = (GS_INPUT)0;
    
    Out.Position = mul( In.position, worldMatrix ); 
    
	Out.TexCoord = In.tex.yx;   

    //Out.Normal   = mul(float3(0,0,-1),  (float3x3)worldMatrix);
	Out.Normal   = mul(In.normal,  (float3x3)worldMatrix);

    //Out.Tangent  = mul(float3(0,1,0), (float3x3)worldMatrix);
    Out.Tangent  = mul(In.tangent, (float3x3)worldMatrix);


    return Out;
}

[maxvertexcount(4)] 
void GSSilhouette( triangle GS_INPUT In[3], inout TriangleStream<PixelInputType> EdgeStream )
{
	int	    iSign[3] = { 0,0,0 };
	float   NdotV[3] = { 0,0,0 };

	float3  newPosition[2] = { 0,0,0, 0,0,0 };
	float3  newNormal  [2] = { 0,0,0, 0,0,0 };
	float3  newTangent [2] = { 0,0,0, 0,0,0 };
	float2  newTexCoord[2] = { 0,0,   0,0 };

	float3 View = 0;

	int isign = 0;

	[unroll]
	for( int i = 0; i < 3; i++ )
	{
		View = In[i].viewDirection;
		
		NdotV[i] = dot( normalize( In[i].Normal ), normalize( View ) );
        iSign[i] = NdotV[i] > 0;
		NdotV[i] = abs( NdotV[i] );
		isign += iSign[i];
	}

	if( isign == 1 || isign == 2 )
	{
		float3 Float;
		
		Float.x = NdotV[0] / ( NdotV[0] + NdotV[1] );
		Float.y = NdotV[1] / ( NdotV[1] + NdotV[2] );
		Float.z = NdotV[2] / ( NdotV[2] + NdotV[0] );

		int curIndex = 0;

		if( ( iSign[0] ^ iSign[1] ) != 0 )
		{		
			newTexCoord [curIndex] = lerp( In[0].TexCoord,     In[1].TexCoord,     Float.x );
			newTangent  [curIndex] = lerp( In[0].Tangent,      In[1].Tangent,      Float.x );
			newPosition [curIndex] = lerp( In[0].Position.xyz, In[1].Position.xyz, Float.x );
			newNormal [curIndex++] = lerp( In[0].Normal,       In[1].Normal,       Float.x );
		}

		if( ( iSign[1] ^ iSign[2] ) != 0 )
		{
			newTexCoord [curIndex] = lerp( In[1].TexCoord,     In[2].TexCoord,     Float.y );
			newTangent  [curIndex] = lerp( In[1].Tangent,      In[2].Tangent,      Float.y );
			newPosition [curIndex] = lerp( In[1].Position.xyz, In[2].Position.xyz, Float.y );
			newNormal [curIndex++] = lerp( In[1].Normal,       In[2].Normal,       Float.y );
		}

		if( ( iSign[2] ^ iSign[0] ) != 0 )
		{
			newTexCoord [curIndex] = lerp( In[2].TexCoord,     In[0].TexCoord,     Float.z );
			newTangent  [curIndex] = lerp( In[2].Tangent,      In[0].Tangent,      Float.z );
			newPosition [curIndex] = lerp( In[2].Position.xyz, In[0].Position.xyz, Float.z );
			newNormal [curIndex++] = lerp( In[2].Normal,       In[0].Normal,       Float.z );
		}

		if( curIndex != 0 )
		{ 
			float3 PositionWS[4];	

			PositionWS[0] = newPosition[0]; 
			PositionWS[1] = newPosition[0] + normalize(newNormal[0]) * g_ExtrudeFin;
			PositionWS[2] = newPosition[1]; 
			PositionWS[3] = newPosition[1] + normalize(newNormal[1]) * g_ExtrudeFin;

			PixelInputType Out = (PixelInputType)0;

			Out.Position  = mul( float4(PositionWS[0], 1.0f), worldViewProjectionMatrix );
			Out.TexCoord  = newTexCoord[0];
			Out.Normal    = newNormal[0];
			Out.Tangent   = newTangent[0];
			Out.PosWS	  = float4( PositionWS[0], 0);

			EdgeStream.Append( Out );

			Out.Position  = mul( float4(PositionWS[1], 1.0f), worldViewProjectionMatrix );
			Out.TexCoord  = newTexCoord[0];
			Out.Normal    = newNormal[0];
			Out.Tangent   = newTangent[0];	
			Out.PosWS	  = float4( PositionWS[1], 1);

			EdgeStream.Append( Out );

			Out.Position  = mul( float4(PositionWS[2], 1.0f), worldViewProjectionMatrix );
			Out.TexCoord  = newTexCoord[1];
			Out.Normal    = newNormal[1];
			Out.Tangent   = newTangent[1];	
			Out.PosWS	  = float4( PositionWS[2], 0);
			
			EdgeStream.Append( Out );

			Out.Position  = mul( float4(PositionWS[3], 1.0f), worldViewProjectionMatrix );
			Out.TexCoord  = newTexCoord[1];
			Out.Normal    = newNormal[1];
			Out.Tangent   = newTangent[1];		
			Out.PosWS	  = float4( PositionWS[3], 1);

			EdgeStream.Append( Out );

			EdgeStream.RestartStrip();
		}
	}
}


float4 PSSilhouette( PixelInputType In ) : SV_Target
{
	float3 ViewWS = In.viewDirection;

	float3 Normal  = normalize( In.Normal  );
	float3 Tangent = normalize( In.Tangent );

	float3 ViewTS  = ToTangentSpace(Normal, Tangent, ViewWS);
	//float3 ViewTS  = float3(0,0,1);

	float2 texShift = ParallaxVector(ViewTS);
	
#ifdef N_DOT_V_LERPING    
	float fCoarseSteps = lerp(g_CoarseStepsMin, g_CoarseStepsMax, abs(dot( normalize(Normal), normalize(ViewWS) )) );
	float fDetailSteps = lerp(g_DetailStepsMin, g_DetailStepsMax, abs(dot( normalize(Normal), normalize(ViewWS) )) );
#else
    float fCoarseSteps = g_CoarseStepsMax;
    float fDetailSteps = g_DetailStepsMax;
#endif

	float2 currPoint = texShift * g_Sign + In.TexCoord;
    float2 tStep = texShift / float( fCoarseSteps );

    float hStep = (1.0f - In.PosWS.w) / float( fCoarseSteps );
    float currHeight  = 1.0f;

    float textureHeight;

    float   i;
    float   j = 0;
	float   k = 0;
	float   m = 0;

	float mipLevel = CalculateMipLevel( In.TexCoord );

	textureHeight = TraceLinear(shaderTexture[2], currPoint, currHeight, tStep, hStep, mipLevel, fCoarseSteps, j);

	if (!j)
	{
		textureHeight = TraceLinear(shaderTexture[2], currPoint, currHeight, tStep, -hStep, mipLevel, fCoarseSteps, k);
	
		j+=k;	
	}

#ifdef BINARY_SEARCH
		if (j)
			textureHeight = TraceBinary(shaderTexture[2], currPoint, currHeight, tStep, hStep, mipLevel, fDetailSteps, 0.001f);
#else
		if (j)
		{
			tStep /= (fDetailSteps + 1);
			hStep /= (fDetailSteps + 1);
		
			textureHeight = TraceLinear(shaderTexture[2], currPoint, currHeight, tStep, hStep, mipLevel, fCoarseSteps, m);
			
			j+=m;
		}
#endif
    if (j == 0) discard;

    float3   LightTS = ToTangentSpace(Normal, Tangent, normalize(lightDirection.xyz - In.PosWS.xyz));

    float fSelfShadowing = 1.0f;

	float4 Out = Lighting( currPoint, normalize(LightTS), ViewTS, fSelfShadowing, mipLevel );
    return Out;
	//return float4(0,0,0,0);
	
}

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 PSReliefMapping( PixelInputType In ) : SV_Target
{
	float3 ViewWS = In.viewDirection;

	float3 Normal  = normalize(In.Normal);
	float3 Tangent = normalize(In.Tangent);

	float3 ViewTS = ToTangentSpace(Normal, Tangent, ViewWS);

	float2 texShift = ParallaxVector(ViewTS);

#ifdef N_DOT_V_LERPING    
	float fCoarseSteps = lerp(g_CoarseStepsMin, g_CoarseStepsMax, abs(dot( Normal, normalize(ViewTS) )) );
	float fDetailSteps = lerp(g_DetailStepsMin, g_DetailStepsMax, abs(dot( Normal, normalize(ViewTS) )) );
#else
    float fCoarseSteps = g_CoarseStepsMax + 1;
    float fDetailSteps = g_DetailStepsMax + 1;
#endif

	float2 currPoint = texShift * g_Sign + In.TexCoord; 
    float2 tStep = texShift / float( fCoarseSteps );

    float hStep = 1.0f / float( fCoarseSteps );
    float currHeight  = 1.0f;
    
    float textureHeight = 1.0f;

    float i;
    float j = 0.0f;

	float mipLevel = CalculateMipLevel( In.TexCoord );

	textureHeight = TraceLinear(shaderTexture[2], currPoint, currHeight, tStep, hStep, 0, fCoarseSteps, j);

#ifdef BINARY_SEARCH
    if (j)	textureHeight = TraceBinary(shaderTexture[2], currPoint, currHeight, tStep, hStep, 0, fDetailSteps, 0.001f);
#else
    if (j) {
	    tStep /= (fDetailSteps + 1);
	    hStep /= (fDetailSteps + 1);
		
	    textureHeight = TraceLinear(shaderTexture[2], currPoint, currHeight, tStep, hStep, 0, fDetailSteps, j);
    }
#endif

	float d2 = currHeight - textureHeight;
	float d1 = currHeight - hStep - (1.0f - shaderTexture[2].SampleLevel( sLinear, currPoint - tStep, 0 ).x);
	float d  = d2 - d1;

	float parallaxlength = ((currHeight - hStep) * d2 - (currHeight) * d1) / d;

	currPoint = In.TexCoord + texShift * ( parallaxlength - 1.0f + g_Sign );

    float3   LightTS = ToTangentSpace(Normal, Tangent, normalize(lightDirection.xyz - In.PosWS.xyz));

    float fSelfShadowing = 1.0f;

	float4 Out;

	Out = Lighting( currPoint, normalize(LightTS), ViewTS, fSelfShadowing, mipLevel );
    //Shadow
	Out *= Shadowing(In.Normal, In.viewDirection,	In.lightViewPosition,	In.lightPos);
	return Out;
	//return float4(shaderTexture[2].Sample(SampleType, In.TexCoord).rgb ,0);
}


////////////////////////////////////////////////////////////////////////////////
// Technique
////////////////////////////////////////////////////////////////////////////////
technique10 LightTechnique
{
    pass pass0
    {
        SetVertexShader(CompileShader(vs_4_0, LightVertexShader()));
		SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_4_0, PSReliefMapping()));
    }

	//pass P1
 //   {    
 //       SetVertexShader  ( CompileShader( vs_4_0, VSSilhouette() ) );
 //       SetGeometryShader( CompileShader( gs_4_0, GSSilhouette() ) );
 //       SetPixelShader   ( CompileShader( ps_4_0, PSSilhouette() ) );
 //       //SetRasterizerState( DisableCulling );
 //   }
}