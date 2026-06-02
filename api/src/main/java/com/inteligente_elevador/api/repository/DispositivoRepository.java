package com.inteligente_elevador.api.repository;

import com.inteligente_elevador.api.domain.Dispositivo;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.Optional;
import java.util.UUID;

public interface DispositivoRepository extends JpaRepository<Dispositivo, UUID> {
    Optional<Dispositivo> findDispositivoByIdentificadorPlaca(String identificadorPlaca);
}
