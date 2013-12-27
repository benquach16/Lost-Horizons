float4x4    matWorldViewProj;


//TEXTURE 0 IS THE FIRST PASS
texture2D ColorMap;
sampler2D ColorMapSampler
{
    Texture = <ColorMap>;   MinFilter = linear; MagFilter = linear; MipFilter = linear;
};

texture2D ColorMap2;
sampler2D ColorMapSampler2
{
    Texture = <ColorMap2>;   MinFilter = linear; MagFilter = linear; MipFilter = linear;
};

struct VERTEXOUTPUT
{ 
    float4 Position: POSITION; 
    float3 TexCoordinate:    TEXCOORD0; 
};

//we use the same vertex shader function
VERTEXOUTPUT VertexShaderFunction(VERTEXOUTPUT input) 
{
    VERTEXOUTPUT ret = (VERTEXOUTPUT) 0; 
    ret.Position = mul(input.Position, matWorldViewProj); 
    ret.TexCoordinate = input.TexCoordinate;

    return ret; 
}

float4 adjustSaturation(float4 color, float saturation)
{
	float grey = dot(color, float3(0.3, 0.59, 0.11));
	return lerp(grey, color, saturation);
}

float Pixels[13] =
{
   -6,
   -5,
   -4,
   -3,
   -2,
   -1,
    0,
    1,
    2,
    3,
    4,
    5,
    6,
};

float BlurWeights[13] =
{
   0.002216,
   0.008764,
   0.026995,
   0.064759,
   0.120985,
   0.176033,
   0.199471,
   0.176033,
   0.120985,
   0.064759,
   0.026995,
   0.008764,
   0.002216,
};
float screenWidth;
float4 PixelShaderFunction(VERTEXOUTPUT input) : COLOR
{
	float4 bloom = tex2D(ColorMapSampler, input.TexCoordinate);
	float4 color = tex2D(ColorMapSampler2, input.TexCoordinate);
	bloom = adjustSaturation(bloom, 1.0) * 1.3;
	//float4 color = {0,0,0,1};
	color = adjustSaturation(color,1.0);
	float offset = 0.0011;

	bloom += tex2D(ColorMapSampler, float2(input.TexCoordinate.x + offset, input.TexCoordinate.y + offset));
	bloom += tex2D(ColorMapSampler, float2(input.TexCoordinate.x - offset, input.TexCoordinate.y - offset));
	bloom += tex2D(ColorMapSampler, float2(input.TexCoordinate.x + offset, input.TexCoordinate.y - offset));
	bloom += tex2D(ColorMapSampler, float2(input.TexCoordinate.x - offset, input.TexCoordinate.y + offset));	
	
	//bloom += tex2D(ColorMapSampler, float2(input.TexCoordinate.x - offset, input.TexCoordinate.y));
	//bloom += tex2D(ColorMapSampler, float2(input.TexCoordinate.x + offset, input.TexCoordinate.y));
	//bloom += tex2D(ColorMapSampler, float2(input.TexCoordinate.x, input.TexCoordinate.y + offset));
	//bloom += tex2D(ColorMapSampler, float2(input.TexCoordinate.x, input.TexCoordinate.y - offset));
	bloom = bloom/5;
	//color *= (1-saturate(bloom));
	
	//float greyscale = 0.3 * bloom.r + 0.59 * bloom.g + 0.11 * bloom.b;
	//bloom.r = greyscale * 0.4 + bloom.r * (1 - 0.4);
	//bloom.g = greyscale * 0.4 + bloom.g * (1 - 0.4);
	//bloom.b = greyscale * 0.4 + bloom.b * (1 - 0.4);
	
	//color = pow(color, 1.2);
	return color + bloom;
	
}

