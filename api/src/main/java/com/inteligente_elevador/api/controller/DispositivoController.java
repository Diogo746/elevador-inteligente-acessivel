package com.inteligente_elevador.api.controller;

import com.inteligente_elevador.api.dto.DispositivoDto;
import com.inteligente_elevador.api.dto.DispositivoRetornoDto;
import com.inteligente_elevador.api.dto.StatusDto;
import com.inteligente_elevador.api.service.DispositivoService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.UUID;

@RestController
@RequestMapping("/api/iot/dispositivo")
public class DispositivoController {

    @Autowired
    private DispositivoService dispositivoService;

    @GetMapping
    public ResponseEntity<List<DispositivoRetornoDto>> listar() {
        return ResponseEntity.ok(dispositivoService.ListarDispositivos());
    }

    @PatchMapping("/{id}/status")
    public ResponseEntity<Void> alterarStatus(@PathVariable UUID id) {
        dispositivoService.mudarStatus(id);
        return ResponseEntity.noContent().build();
    }

    @PostMapping("/criar")
    public ResponseEntity<?> criarDispositivo(@RequestBody DispositivoDto dispositivoDto) {
        dispositivoService.CriarDispositivo(dispositivoDto);
        return ResponseEntity.status(HttpStatus.CREATED).build();
    }

}
