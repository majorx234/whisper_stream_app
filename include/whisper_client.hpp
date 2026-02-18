/*
 * This file is part of the whisper_stream_app distribution (https://github.com/majorx234/whisper_stream_app ).
 * Copyright (c) 2026 Majorx234
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef WHISPER_CLIENT_HPP_
#define WHISPER_CLIENT_HPP_

#include "whisper.h"

#include <string>
#include <thread>

struct whisper_params {
    int32_t n_threads  = std::min(4, (int32_t) std::thread::hardware_concurrency());
    int32_t step_ms    = 3000;
    int32_t length_ms  = 10000;
    int32_t keep_ms    = 200;
    int32_t max_tokens = 32;
    int32_t audio_ctx  = 0;
    int32_t beam_size  = -1;

    float vad_thold    = 0.6f;
    float freq_thold   = 100.0f;

    bool translate     = false;
    bool no_fallback   = false;
    bool print_special = false;
    bool no_context    = true;
    bool no_timestamps = false;
    bool tinydiarize   = false;
    bool use_gpu       = true;
    bool flash_attn    = true;
    bool debug         = false;
    bool use_vad       = false;

    std::string language   = "de";
    std::string model      = "models/ggml-model.bin";
    std::string fname_out;

    std::string format     = "models/ggml-silero-v6.2.0.bin";
    int32_t     sample_rate = WHISPER_SAMPLE_RATE;

    int32_t vad_probe_ms    = 200;
    int32_t vad_silence_ms  = 800;
    int32_t vad_pre_roll_ms = 300;

    std::string vad_model   = "";       // path to silero .bin model
};

class WhisperClient{
  public:
    WhisperClient(whisper_params params);
    ~WhisperClient();

    bool resume();
    bool pause();
    bool clear();
  private:
    void reader_loop();
};

#endif //WHISPER_CLIENT_HPP_
