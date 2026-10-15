clear; clc; close all;

dados = readmatrix('contagem.csv', 'NumHeaderLines', 1);

numero = dados(:, 1);
comp_lista = dados(:, 2);
comp_abb = dados(:, 3);

media_lista = mean(comp_lista);
media_abb = mean(comp_abb);

fprintf('Sorteios: %d\n', numel(numero));
fprintf('Media de comparacoes na lista: %.2f\n', media_lista);
fprintf('Media de comparacoes na ABB:   %.2f\n', media_abb);

figure('Name', 'Lista x ABB', 'Color', 'w');

% Gráfico 1: as duas estruturas na mesma escala
subplot(1, 1, 1);
plot(numero, comp_lista, 'r-', 'LineWidth', 2);
hold on;
plot(numero, comp_abb, 'b-', 'LineWidth', 1.5);
hold off;
grid on;
xlabel('Numero sorteado');
ylabel('Comparacoes');
title(sprintf('Lista x ABB ', media_lista, media_abb));
legend('Lista Encadeada', 'Arvore de Busca Binaria', 'Location', 'best');

% Gráfico 2: só a ABB, para enxergar a variação dela
%subplot(2, 1, 2);
%plot(numero, comp_abb, 'b-', 'LineWidth', 1.5);
%grid on;
%xlabel('Numero sorteado');
%ylabel('Comparacoes');
%title('Arvore de Busca Binaria (escala ampliada)');
