////////////////////////////////////////////////////////////////////////////////
// Filename: shadow.fx
// http://rastertek.com/dx10tut40.html
////////////////////////////////////////////////////////////////////////////////
matrix lightViewMatrix;
matrix lightProjectionMatrix;

//////////////
// TEXTURES //
//////////////
Texture2D depthMapTexture;

///////////////////
// SAMPLE STATES //
///////////////////
SamplerState SampleTypeClamp
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Clamp;
    AddressV = Clamp;
};


/////////////
// GLOBALS //
/////////////
float3 lightPosition;
float3 cameraPosition;

float4 Shadowing(float3 normal, float3 viewDirection,	float4 lightViewPosition,	float3 lightPos)
{
	float bias;
    float4 color;
	float2 projectTexCoord;
	float depthValue;
	float lightDepthValue;
    float lightIntensity;


	// Set the bias value for fixing the floating point precision issues.
	bias = 0.001f;

	// Set the default output color to be black (shadow).
    color = float4(0.4, 0.4, 0.4, 1.0f);

	// Calculate the projected texture coordinates.
	projectTexCoord.x =  lightViewPosition.x / lightViewPosition.w / 2.0f + 0.5f;
	projectTexCoord.y = -lightViewPosition.y / lightViewPosition.w / 2.0f + 0.5f;

	// Determine if the projected coordinates are in the 0 to 1 range.  If so then this pixel is in the view of the light.
	if((saturate(projectTexCoord.x) == projectTexCoord.x) && (saturate(projectTexCoord.y) == projectTexCoord.y))
	{
		// Sample the shadow map depth value from the depth texture using the sampler at the projected texture coordinate location.
		depthValue = depthMapTexture.Sample(SampleTypeClamp, projectTexCoord).r;

		// Calculate the depth of the light.
		lightDepthValue = lightViewPosition.z / lightViewPosition.w;

		// Subtract the bias from the lightDepthValue.
		lightDepthValue = lightDepthValue - bias;

		// Compare the depth of the shadow map value and the depth of the light to determine whether to shadow or to light this pixel.
		// If the light is in front of the object then light the pixel, if not then shadow this pixel since an object (occluder) is casting a shadow on it.
		if(lightDepthValue < depthValue)
		{
		    // Calculate the amount of light on this pixel.
			lightIntensity = saturate(dot(normal, lightPos));

			// If this pixel is illuminated then set it to pure white (non-shadow).
		    if(lightIntensity > 0.0f)
			{
				color = (lightIntensity) * 5;
				color = saturate(color);
				
				color.x = clamp(color.x, 0.4, 1);
				color.y = clamp(color.y, 0.4, 1);
				color.z = clamp(color.z, 0.4, 1);
			}
		}
	}

    return color;
}