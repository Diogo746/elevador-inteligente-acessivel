package com.inteligente_elevador.api.service;


import com.inteligente_elevador.api.domain.Dispositivo;
import com.inteligente_elevador.api.exception.DispositivoInativoException;
import com.inteligente_elevador.api.repository.DispositivoRepository;
import com.inteligente_elevador.api.repository.EventoRepository;
import jakarta.persistence.EntityExistsException;
import jakarta.persistence.EntityNotFoundException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

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

       String placaLimpa = identificador.trim();

       return dispositivoRepository.findDispositivoByIdentificadorPlaca(placaLimpa).orElseThrow(() -> new EntityNotFoundException("Placa não encontrada."));
    }
}
