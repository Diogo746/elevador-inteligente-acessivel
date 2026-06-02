package com.inteligente_elevador.api.domain;


import com.inteligente_elevador.api.enums.TipoEvento;
import jakarta.persistence.*;
import lombok.Getter;
import lombok.Setter;

import java.time.LocalDate;
import java.time.LocalTime;
import java.util.UUID;

@Entity(name = "Eventos")
@Getter
@Setter
public class Evento {
    @Id
    @GeneratedValue(strategy = GenerationType.UUID)
    private UUID id;

    @ManyToOne
    @JoinColumn(name = "dispositivo_id")
    private Dispositivo id_dispositivos;

    @Column(nullable = false)
    private TipoEvento tipo_evento;

    @Column(nullable = false)
    private LocalDate data_evento;

    @Column(nullable = false)
    private LocalTime hora_evento;

    public Evento() {}


    public Evento(Dispositivo id_dispositivos, TipoEvento tipo_evento, LocalDate data_evento, LocalTime hora_evento) {
        this.id_dispositivos = id_dispositivos;
        this.tipo_evento = tipo_evento;
        this.data_evento = data_evento;
        this.hora_evento = hora_evento;
    }
}
