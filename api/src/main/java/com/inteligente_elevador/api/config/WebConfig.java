package com.inteligente_elevador.api.config;

import com.inteligente_elevador.api.security.InterceptadorPlaca;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.InterceptorRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

@Configuration
public class WebConfig implements WebMvcConfigurer {
    @Autowired
    private InterceptadorPlaca interceptador;

    @Override
    public void addInterceptors(InterceptorRegistry registry) {
        registry.addInterceptor(interceptador).addPathPatterns("/api/iot/evento/**");
    }
}
