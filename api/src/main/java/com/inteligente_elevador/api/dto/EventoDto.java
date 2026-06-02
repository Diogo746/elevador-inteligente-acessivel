package com.inteligente_elevador.api.dto;

import com.inteligente_elevador.api.enums.TipoEvento;
import jakarta.validation.constraints.NotBlank;

import java.time.LocalDate;
import java.time.LocalTime;

public record EventoDto(
        @NotBlank(message = "Idenficador da placa não pode está vazio")
        String idenficadorPlaca,

        @NotBlank(message = "informe o tipo do evento")
        TipoEvento tipoEvento,

        @NotBlank(message = "informe a data do evento")
        LocalDate dataEvento,

        @NotBlank(message = "informe a hora do evento")
        LocalTime horaEvento
) {
}
