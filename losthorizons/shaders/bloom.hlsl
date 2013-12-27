float4x4    matWorldViewProj;
float screenWidth;

 
struct VERTEXOUTPUT
{ 
        float4 Position: POSITION; 
        float3 TexCoordinate:    TEXCOORD0; 
};
 

sampler2D ColorMapSampler : register(s0);



float bloomThreshold = 0.3;
 
 
VERTEXOUTPUT VertexShaderFunction(VERTEXOUTPUT input) 
{
    VERTEXOUTPUT ret = (VERTEXOUTPUT) 0; 
    ret.Position = mul(input.Position, matWorldViewProj); 
    ret.TexCoordinate = input.TexCoordinate;

    return ret; 
}


float4 PixelShaderFunction(VERTEXOUTPUT input) : COLOR
{       
    float4 color = tex2D(ColorMapSampler, input.TexCoordinate);    

	float4 bloom = saturate((color-0.2)/(1-0.2));

	return bloom;


}

