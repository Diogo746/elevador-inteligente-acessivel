package com.inteligente_elevador.api.security;

import com.inteligente_elevador.api.domain.Dispositivo;
import com.inteligente_elevador.api.exception.DispositivoInativoException;
import com.inteligente_elevador.api.service.DispositivoService;
import jakarta.persistence.EntityExistsException;

import jakarta.persistence.EntityNotFoundException;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import org.springframework.web.servlet.HandlerInterceptor;

@Component
public class InterceptadorPlaca implements HandlerInterceptor {
    @Autowired
    DispositivoService dispositivoService;

    @Override
    public boolean preHandle(HttpServletRequest request,
                             HttpServletResponse response,
                             Object handler) throws Exception {

        String idPlaca = request.getHeader("idPlaca");

        if (idPlaca == null || idPlaca.isBlank()) {
            response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
            response.setContentType("text/plain;charset=utf-8");
            response.getWriter().write("Acesso negado: Identificador da placa não fornecido");
            return false;
        }

        try {
            Dispositivo dispositivo = dispositivoService.EncontrarPorIdentificador(idPlaca);

            dispositivoService.PlacaAtiva(dispositivo);

            request.setAttribute("placaAutenticada", dispositivo);

            return true;
        } catch (EntityNotFoundException e) {
            response.setStatus(HttpServletResponse.SC_FORBIDDEN);
            response.setContentType("text/plain;charset=utf-8");
            response.getWriter().write("Acesso negado: Placa não cadastrada no sistema");
            return false;
        } catch (DispositivoInativoException e) {
            response.setStatus(HttpServletResponse.SC_FORBIDDEN);
            response.setContentType("text/plain;charset=utf-8");
            response.getWriter().write("Acesso negado: " + e.getMessage());
            return false;
        } catch (IllegalArgumentException e) {
            response.setStatus(HttpServletResponse.SC_FORBIDDEN);
            response.setContentType("text/plain;charset=utf-8");
            response.getWriter().write("Acesso negado: " + e.getMessage());
            return false;
        }
    }
}
