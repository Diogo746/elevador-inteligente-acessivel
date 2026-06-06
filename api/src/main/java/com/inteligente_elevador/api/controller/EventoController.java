package com.inteligente_elevador.api.controller;

import com.inteligente_elevador.api.domain.Dispositivo;
import com.inteligente_elevador.api.dto.EventoDto;
import com.inteligente_elevador.api.service.privado.EventoService;
import jakarta.servlet.http.HttpServletRequest;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController()
@RequestMapping("/api/iot/evento")
public class EventoController {
    @Autowired
    private EventoService eventoService;

    @PostMapping("/criar")
    public ResponseEntity<?> criarEvento(@RequestBody EventoDto eventoDto, HttpServletRequest request) {
        Dispositivo placa = (Dispositivo)request.getAttribute("placaAutenticada");

        eventoService.Save(eventoDto, placa);

        return ResponseEntity.status(HttpStatus.CREATED).build();
    }
}
