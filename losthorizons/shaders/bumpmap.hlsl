float4x4    matWorldViewProj;
float4x4    World;
float4      LightDirection;
float4      EyePosition;
float       usenmap;
 
struct VERTEXOUTPUT
{ 
        float4 Position: POSITION; 
        float3 TexCoordinate:    TEXCOORD0; 
        float3 N:    TEXCOORD1; 
        float3 V:    TEXCOORD2;
        float3 T:   TEXCOORD3;
        float3 NORMAL: NORMAL;
        float3x3 WorldToTangentSpace : TEXCOORD4;
 
        float3 Binormal : BINORMAL0;
        float3 Tangent : TANGENT0;
 
 
};
 
texture2D ColorMap;
sampler2D ColorMapSampler
{
    Texture = <ColorMap>;   MinFilter = linear; MagFilter = linear; MipFilter = linear;
};
 
texture2D NormalMap;
sampler2D NormalMapSampler
{
    Texture = <NormalMap>;  MinFilter = linear; MagFilter = linear; MipFilter = linear;
};
 
 
 
 
VERTEXOUTPUT VertexShaderFunction(VERTEXOUTPUT input) 
{
    VERTEXOUTPUT ret = (VERTEXOUTPUT) 0; 
    ret.Position = mul(input.Position, matWorldViewProj); 
    ret.T = input.TexCoordinate;   
    ret.TexCoordinate = normalize(LightDirection); 
    ret.N = normalize(mul(input.NORMAL, World)); 
    
    float4 PosWorld = mul(input.Position, World);
    ret.V = normalize(EyePosition - PosWorld);
 
 
    ret.WorldToTangentSpace[0] = mul(normalize(input.Tangent), World);
    ret.WorldToTangentSpace[1] = mul(normalize(input.Binormal), World);
    ret.WorldToTangentSpace[2] = mul(normalize(input.NORMAL), World);
 
    return ret; 
}
 
 
float4 PixelShaderFunction(VERTEXOUTPUT I) : COLOR
{       
    float4 color = tex2D(ColorMapSampler, I.T);    
    float3 normalMap = 2 * tex2D(NormalMapSampler, I.T) - 1;   
    float3 normalMap2 = normalize(mul(normalMap, I.WorldToTangentSpace));
    float4 normal;
    float4 normal2;
    if (usenmap == 1) normal = float4(normalMap2,1.0);
    if (usenmap == 0) normal2 = float4(normalMap,1);
 
    normal = float4(normalMap2,1.0);
    normal2 = float4(normalMap,1);
    
    float Diff = saturate(dot(-I.TexCoordinate, normal));
    float Diff2 = saturate(dot(-I.TexCoordinate, normal2));
 
    float Ai = 0.1f; 
    float4 Ac = float4(.1, .1, .1, .2);
    float Di = 1.5f; 
    float4 Dc = float4(1, 1, 1, .5); 
    float4 Sc = float4(1, 1, 1.0, 1.0);
 
 
    float3 R = saturate(reflect(I.TexCoordinate,normal));    
    float3 R2 = saturate(reflect(I.TexCoordinate,normal2));   
 
    float Specular = pow(dot(R, I.V), 5); // R.V^n
    float Specular2 = pow(dot(R2, I.V), 5); // R.V^n   
    
    float4 color1 = color * Di * Dc * Diff + color * Sc * Specular * Ai * Ac;
    float4 color2 = color * Di * Dc * Diff2 * (Diff + (.05,.05,.05,.05)) * 6; 
    
        if (usenmap == 1) color2 = (0,0,0,0);
    
    return color1 + color2 ;
 
 
}