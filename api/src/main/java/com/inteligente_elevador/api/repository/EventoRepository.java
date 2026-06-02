package com.inteligente_elevador.api.repository;

import com.inteligente_elevador.api.domain.Evento;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.UUID;

public interface EventoRepository extends JpaRepository<Evento, UUID> {
}
