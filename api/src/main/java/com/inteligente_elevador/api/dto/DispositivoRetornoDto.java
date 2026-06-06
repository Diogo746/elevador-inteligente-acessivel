package com.inteligente_elevador.api.dto;

import com.fasterxml.jackson.annotation.JsonProperty;
import com.inteligente_elevador.api.domain.Dispositivo;

import java.util.UUID;

public record DispositivoRetornoDto(
        UUID id,

        @JsonProperty("identificador_placa")
        String identificadorPlaca,

        @JsonProperty("apelido_placa")
        String apelidoPlaca,

        boolean ativo
) {
    public static DispositivoRetornoDto fromEntity(Dispositivo dispositivo) {
        return new DispositivoRetornoDto(
                dispositivo.getId(),
                dispositivo.getIdentificadorPlaca(),
                dispositivo.getApelidoPlaca(),
                dispositivo.isAtivo()
        );
    }
}