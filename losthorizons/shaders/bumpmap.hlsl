float4x4    matWorldViewProj;
float4x4    World;
float4      LightDirection;
float4      EyePosition;
float       usenmap;
 
struct OUT
{ 
        float4 Pos: POSITION; 
        float3 L:    TEXCOORD0; 
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
 
 
 
 
OUT VertexShaderFunction( OUT I) 
{
    OUT Out = (OUT) 0; 
    Out.Pos = mul(I.Pos, matWorldViewProj); 
    Out.T = I.L;   
    Out.L = normalize(LightDirection); 
    Out.N = normalize(mul(I.NORMAL, World)); 
    
    float4 PosWorld = mul(I.Pos, World);
    Out.V = normalize(EyePosition - PosWorld);
 
 
    Out.WorldToTangentSpace[0] = mul(normalize(I.Tangent), World);
    Out.WorldToTangentSpace[1] = mul(normalize(I.Binormal), World);
    Out.WorldToTangentSpace[2] = mul(normalize(I.NORMAL), World);
 
    return Out; 
}
 
 
float4 PixelShaderFunction(OUT I) : COLOR
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
    
    float Diff = saturate(dot(-I.L, normal));
    float Diff2 = saturate(dot(-I.L, normal2));
 
    float Ai = 0.1f; 
    float4 Ac = float4(.1, .1, .1, .2);
    float Di = 1.5f; 
    float4 Dc = float4(1, 1, 1, .5); 
    float4 Sc = float4(1, 1, 1.0, 1.0);
 
 
    float3 R = saturate(reflect(I.L,normal));    
    float3 R2 = saturate(reflect(I.L,normal2));   
 
    float Specular = pow(dot(R, I.V), 5); // R.V^n
    float Specular2 = pow(dot(R2, I.V), 5); // R.V^n   
    
    float4 color1 = color * Di * Dc * Diff + color * Sc * Specular * Ai * Ac;
    float4 color2 = color * Di * Dc * Diff2 * (Diff + (.05,.05,.05,.05)) * 6; 
    
        if (usenmap == 1) color2 = (0,0,0,0);
    
    return color1 + color2 ;
 
 
}