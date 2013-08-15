float4x4    matWorldViewProj;

 
struct VERTEXOUTPUT
{ 
        float4 Position: POSITION; 
        float3 TexCoordinate:    TEXCOORD0; 
};
 
texture2D ColorMap;
sampler2D ColorMapSampler
{
    Texture = <ColorMap>;   MinFilter = linear; MagFilter = linear; MipFilter = linear;
};



float bloomThreshold = 0.3;
 
 
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
    float4 color = tex2D(ColorMapSampler, input.TexCoordinate);    

	float4 bloom = saturate((color-0.2)/(1-0.2));

	return bloom;
	//bloom = adjustSaturation(bloom, 1.0) * 1.3;
	//color = adjustSaturation(color, 1.0);
	//bloom += tex2D(ColorMapSampler, float2(input.TexCoordinate.x + 0.002f, input.TexCoordinate.y += 0.002f));
	//bloom += tex2D(ColorMapSampler, float2(input.TexCoordinate.x - 0.002f, input.TexCoordinate.y -= 0.002f));
	//bloom += tex2D(ColorMapSampler, float2(input.TexCoordinate.x + 0.002f, input.TexCoordinate.y -= 0.002f));
	//bloom += tex2D(ColorMapSampler, float2(input.TexCoordinate.x - 0.020f, input.TexCoordinate.y += 0.002f));
	//bloom = bloom/4;
	//color *= (1-saturate(bloom));
	//return color + bloom;

}

