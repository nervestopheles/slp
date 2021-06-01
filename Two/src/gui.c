void Intro(SDL_Window *window, struct nk_context* nk_ctx)
{
    if (screen_width >= screen_height)
        screen_gaps = screen_width;
    else if (screen_width < screen_height)
        screen_gaps = screen_height;

    struct nk_color table[NK_COLOR_COUNT];
    table[NK_COLOR_WINDOW] = nk_rgba(60, 60, 60, 25);
    table[NK_COLOR_TEXT] = nk_rgba(180, 180, 180, 255);
    nk_style_from_table(nk_ctx, table);

    while (screen_gaps > default_screen_gaps)
    {
        GetEvent(window, nk_ctx);
        screen_gaps -= gaps_step;
        UpdateMenuPosition(&main_menu, main_menu_gaps);
        Render(window, nk_ctx);
    }
}
