package com.inteligente_elevador.api.dto;

import com.fasterxml.jackson.annotation.JsonProperty;
import jakarta.validation.constraints.NotBlank;

public record DispositivoDto(
        @NotBlank(message = "identificador não informado")
        @JsonProperty("identificador_placa")
        String identificador_placa,

        @NotBlank(message = "informe um apelido para a placa")
        @JsonProperty("apelido_placa")
        String apelido_placa,

        Boolean ativo
) {
}
