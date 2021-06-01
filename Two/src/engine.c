void UpdateMenuPosition(struct nk_rect *menu,
    int x, int y, int w, int h)
{
    menu->x = x; menu->y = y;
    menu->w = w; menu->h = h;
}

void SetFont(struct nk_context *nk_ctx,
    const char *font_path, const unsigned char font_size)
{
    struct nk_font_atlas *atlas;
    nk_sdl_font_stash_begin(&atlas);
    struct nk_font *font = nk_font_atlas_add_from_file(
        atlas, font_path, font_size, 0);
    nk_sdl_font_stash_end();
    nk_style_set_font(nk_ctx, &font->handle);
}

int Event(SDL_Window *window, SDL_Event evt)
{
    switch (evt.type) {
        case SDL_WINDOWEVENT:
            if (evt.window.event == SDL_WINDOWEVENT_RESIZED) {
                SDL_GetWindowSize(window, &screen_width, &screen_height);
                glClear(GL_COLOR_BUFFER_BIT); glFlush();
                SDL_GL_SwapWindow(window);
                UpdateMenuPosition(&main_menu, main_menu_gaps);
            } break;
        case SDL_KEYDOWN:
            if (evt.key.keysym.sym == SDLK_EQUALS) {
                if (screen_gaps*2 < screen_height) {
                    screen_gaps += gaps_step;
                    UpdateMenuPosition(&main_menu, main_menu_gaps);
                }
            }
            if (evt.key.keysym.sym == SDLK_MINUS) {
                if (screen_gaps > default_screen_gaps) {
                    screen_gaps -= gaps_step;
                    UpdateMenuPosition(&main_menu, main_menu_gaps);
                }
            }
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

void Render(SDL_Window *window, struct nk_context* nk_ctx)
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (nk_begin(nk_ctx, "", main_menu,
            NK_WINDOW_BORDER
            | NK_WINDOW_NO_SCROLLBAR
            | NK_WINDOW_BACKGROUND)) {
        nk_layout_row_dynamic(nk_ctx, (screen_height-screen_gaps*2.0)/5.0, 1);
        nk_spacing(nk_ctx, 2);
        nk_label(nk_ctx, "Hello World!", NK_TEXT_CENTERED);
    }
    nk_end(nk_ctx);

    nk_sdl_render(
        NK_ANTI_ALIASING_OFF,
        MAX_VERTEX_MEMORY,
        MAX_ELEMENT_MEMORY);
    SDL_GL_SwapWindow(window);
}
