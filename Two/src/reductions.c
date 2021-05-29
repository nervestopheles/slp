void SetFont(struct nk_context *nk_ctx, const char *font_path)
{
    struct nk_font_atlas *atlas;
    nk_sdl_font_stash_begin(&atlas);
    struct nk_font *font = nk_font_atlas_add_from_file(atlas, font_path, 12, 0);
    nk_sdl_font_stash_end();
    nk_style_set_font(nk_ctx, &font->handle);
}

int Event(SDL_Window *window, SDL_Event evt)
{
    switch (evt.type) {
        case SDL_WINDOWEVENT:
            if (evt.window.event == SDL_WINDOWEVENT_RESIZED) {
                glClear(GL_COLOR_BUFFER_BIT); glFlush();
                SDL_GL_SwapWindow(window);
            } break;
        case SDL_KEYDOWN:
            if (evt.key.keysym.sym == SDLK_q) return 0;
            break;
        case SDL_QUIT:
            return 0;
    }
    return 1;
}

int GetEvent(SDL_Window *window, struct nk_context *nk_ctx)
{
    static SDL_Event evt;
    nk_input_begin(nk_ctx);
    while(SDL_PollEvent(&evt)) {
        if (!Event(window, evt)) return 0;
        nk_sdl_handle_event(&evt);
    } nk_input_end(nk_ctx);
    return 1;
}