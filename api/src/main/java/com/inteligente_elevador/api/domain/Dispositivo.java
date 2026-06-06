package com.inteligente_elevador.api.domain;

import jakarta.persistence.*;
import lombok.Getter;
import lombok.Setter;

import java.util.UUID;

@Entity(name = "dispositivos")
@Getter
@Setter
public class Dispositivo {
    @Id
    @GeneratedValue(strategy = GenerationType.UUID)
    private UUID id;

    @Column(nullable = false, name = "idenficadorPlaca")
    private String identificadorPlaca;

    @Column(nullable = false, name = "apelido_placa")
    private String apelidoPlaca;

    @Column(nullable = false)
    private boolean ativo = true;

    public Dispositivo(String identificadorPlaca, String apelidoPlaca) {
        this.identificadorPlaca = identificadorPlaca;
        this.apelidoPlaca = apelidoPlaca;
    }

    public Dispositivo() {
    }

    public void mudarStatus() {
        this.ativo = !this.ativo;
    }
}
