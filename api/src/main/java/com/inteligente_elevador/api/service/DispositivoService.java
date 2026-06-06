package com.inteligente_elevador.api.service;


import com.inteligente_elevador.api.domain.Dispositivo;
import com.inteligente_elevador.api.dto.DispositivoDto;
import com.inteligente_elevador.api.dto.DispositivoRetornoDto;
import com.inteligente_elevador.api.exception.DispositivoInativoException;
import com.inteligente_elevador.api.repository.DispositivoRepository;
import com.inteligente_elevador.api.repository.EventoRepository;
import jakarta.persistence.EntityExistsException;
import jakarta.persistence.EntityNotFoundException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.UUID;

@Service
public class DispositivoService {

    @Autowired
    private DispositivoRepository dispositivoRepository;


    public void PlacaAtiva(Dispositivo dispositivo) {
        if(dispositivo == null) {
            throw new IllegalArgumentException("O dispositivo não pode ser nulo.");
        }

        if (!dispositivo.isAtivo()) {
            throw new DispositivoInativoException("Acesso negado, placa inativa");
        }
    }

    public Dispositivo EncontrarPorIdentificador(String identificador) {
       if(identificador == null ||  identificador.isBlank()) {
           throw new IllegalArgumentException("O idenficador da placa informada não pode ser nula ou vazia.");
       }

       String placa_limpa = identificador.trim();

       return dispositivoRepository.findDispositivoByIdentificadorPlaca(placa_limpa).orElseThrow(() -> new EntityNotFoundException("Placa não encontrada."));
    }

    public List<DispositivoRetornoDto> ListarDispositivos() {
        return dispositivoRepository.findAll()
                .stream()
                .map(DispositivoRetornoDto::fromEntity)
                .toList();
    }

    @Transactional
    public void CriarDispositivo(DispositivoDto dispositivoDto) {
        String identificador_limpo = dispositivoDto.identificador_placa().trim();
        String apelido_limpo =  dispositivoDto.apelido_placa().trim();

        boolean jaExiste = dispositivoRepository.findDispositivoByIdentificadorPlaca(identificador_limpo).isPresent();
        if(jaExiste) {
            throw new EntityExistsException("Placa já existente.");
        }

        Dispositivo novoDispositivo = new Dispositivo(identificador_limpo,  apelido_limpo);
        dispositivoRepository.save(novoDispositivo);
    }

    @Transactional
    public void mudarStatus(UUID id) {
        Dispositivo dispositivo = dispositivoRepository.findById(id).orElseThrow(() -> new EntityNotFoundException("Placa não encontrada."));
        dispositivo.mudarStatus();
        dispositivoRepository.save(dispositivo);
    }
}
