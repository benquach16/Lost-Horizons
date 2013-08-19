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
	float4 color2 = tex2D(ColorMapSampler2, input.TexCoordinate);
	float greyscale = 0.3 * color.r + 0.59 * color.g + 0.11 * color.b;
	color.r = greyscale * 0.4 + color.r * (1 - 0.4);
	color.g = greyscale * 0.4 + color.g * (1 - 0.4);
	color.b = greyscale * 0.4 + color.b * (1 - 0.4);
	
	color = pow(color, 1.2);
	return color + color2;
}

