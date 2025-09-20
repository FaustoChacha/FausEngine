#version 330 core
        in vec2 TexCoord;
        out vec4 frag_color;
        uniform sampler2D texSampler1;
        void main()
        {
            vec4 texColor = texture(texSampler1, TexCoord);
            if(texColor.a < 0.1) discard;
            frag_color = texColor;
        }