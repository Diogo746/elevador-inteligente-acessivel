package com.inteligente_elevador.api.domain;


import com.inteligente_elevador.api.enums.TipoEvento;
import jakarta.persistence.*;
import lombok.Getter;
import lombok.Setter;

import java.util.UUID;

@Entity
@Getter
@Setter
public class Eventos {
    @Id
    @GeneratedValue(strategy = GenerationType.UUID)
    private UUID id;

    @ManyToOne
    @JoinColumn(name = "dispositivo_id")
    private Dispositivos id_dispositivos;

    @Column(nullable = false)
    private TipoEvento tipo_evento;
}
