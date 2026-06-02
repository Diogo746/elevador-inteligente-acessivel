package com.inteligente_elevador.api.dto;

import com.fasterxml.jackson.annotation.JsonProperty;
import com.inteligente_elevador.api.enums.TipoEvento;
import jakarta.validation.constraints.NotBlank;

import java.time.LocalDate;
import java.time.LocalTime;

public record EventoDto(

        @NotBlank(message = "informe o tipo do evento")
        @JsonProperty("tipo_evento")
        TipoEvento tipoEvento,

        @NotBlank(message = "informe a data do evento")
        @JsonProperty("data_evento")
        LocalDate dataEvento,

        @NotBlank(message = "informe a hora do evento")
        @JsonProperty("hora_evento")
        LocalTime horaEvento
) {
}
