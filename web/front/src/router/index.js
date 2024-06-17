import { createRouter, createWebHashHistory } from 'vue-router'

const routes = [
  {
    path: '/',
    name: 'dashboard',
    component: () => import('@/views/DashboardView.vue')
  },
  {
    path: '/control',
    name: 'control',
    component: () => import('@/views/ControlView.vue')
  }
]

const router = createRouter({
  history: createWebHashHistory(),
  routes
})

export default router
