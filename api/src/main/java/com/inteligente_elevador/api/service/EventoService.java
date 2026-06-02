package com.inteligente_elevador.api.service;


import com.inteligente_elevador.api.domain.Dispositivo;
import com.inteligente_elevador.api.domain.Evento;
import com.inteligente_elevador.api.dto.EventoDto;
import com.inteligente_elevador.api.repository.EventoRepository;
import jakarta.transaction.Transactional;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class EventoService {

    @Autowired
    private EventoRepository eventoRepository;

    @Autowired
    private DispositivoService dispositivoService;

    //continuar aqui dps
    @Transactional
    public void Save(EventoDto eventoDto) {
        Dispositivo placa = dispositivoService.EncontrarPorIdentificador(eventoDto.idenficadorPlaca());

        dispositivoService.PlacaAtiva(placa);

        Evento evento = new Evento(placa, eventoDto.tipoEvento(), eventoDto.dataEvento(), eventoDto.horaEvento());

        eventoRepository.save(evento);

    }

}
