// ¡§¡° Ω¶¿Ã¥ı.
float4 VS_Main(float4 pos : POSITION) : SV_POSITION{
	return pos;
}

// «»ºø Ω¶¿Ã¥ı.
float4 PS_Main(float4 pos : POSITION) : SV_TARGET{
	return float4(1.0f, 1.0f, 0.0f, 1.0f);
}