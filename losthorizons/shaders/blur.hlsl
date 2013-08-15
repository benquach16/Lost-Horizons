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

float4 PixelShaderFunction(VERTEXOUTPUT input) : COLOR
{
	float4 bloom = tex2D(ColorMapSampler, input.TexCoordinate);
	float4 color = tex2D(ColorMapSampler2, input.TexCoordinate);
	bloom = adjustSaturation(bloom, 1.0) * 1.3;
	color = adjustSaturation(color,1.0);
	bloom += tex2D(ColorMapSampler, float2(input.TexCoordinate.x + 0.002f, input.TexCoordinate.y += 0.002f));
	bloom += tex2D(ColorMapSampler, float2(input.TexCoordinate.x - 0.002f, input.TexCoordinate.y -= 0.002f));
	bloom += tex2D(ColorMapSampler, float2(input.TexCoordinate.x + 0.002f, input.TexCoordinate.y -= 0.002f));
	bloom += tex2D(ColorMapSampler, float2(input.TexCoordinate.x - 0.002f, input.TexCoordinate.y += 0.002f));	
	bloom += tex2D(ColorMapSampler, float2(input.TexCoordinate.x - 0.002f, input.TexCoordinate.y));
	bloom += tex2D(ColorMapSampler, float2(input.TexCoordinate.x + 0.002f, input.TexCoordinate.y));
	bloom += tex2D(ColorMapSampler, float2(input.TexCoordinate.x, input.TexCoordinate.y + 0.002f));
	bloom += tex2D(ColorMapSampler, float2(input.TexCoordinate.x, input.TexCoordinate.y - 0.002f));
	bloom = bloom/8;
	color *= (1-saturate(bloom));
	return bloom + color;
	
}

