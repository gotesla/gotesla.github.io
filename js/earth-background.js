(() => {
  const video = document.querySelector('#web_bg video');
  if (!video) return;
  const staticView = matchMedia('(max-width: 767px), (prefers-reduced-motion: reduce)');
  const update = () => {
    if (staticView.matches || navigator.connection?.saveData) {
      video.pause(); video.classList.remove('is-playing');
      if (video.hasAttribute('src')) { video.removeAttribute('src'); video.load(); }
      return;
    }
    if (document.hidden) { video.pause(); return; }
    if (!video.hasAttribute('src')) video.src = '/media/earth-orbit.webm';
    video.play().catch(() => video.classList.remove('is-playing'));
  };
  video.addEventListener('playing', () => video.classList.add('is-playing'));
  video.addEventListener('error', () => video.classList.remove('is-playing'));
  staticView.addEventListener('change', update);
  document.addEventListener('visibilitychange', update);
  update();
})();
