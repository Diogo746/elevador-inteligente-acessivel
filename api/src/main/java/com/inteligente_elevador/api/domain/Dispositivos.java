package com.inteligente_elevador.api.domain;

import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import lombok.Getter;
import lombok.Setter;

import java.util.UUID;

@Entity
@Getter
@Setter
public class Dispositivos {
    @Id
    @GeneratedValue(strategy = GenerationType.UUID)
    private UUID id;
    private String identificador_placa;
    private boolean ativo = true;

    public Dispositivos() {
    }
}
