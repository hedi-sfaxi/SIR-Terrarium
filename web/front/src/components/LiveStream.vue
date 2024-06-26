<template>
    <div id="liveView" class="camView">
        <img :src="imageSrc" alt="Terrarium Live Image" crossorigin='anonymous'>
    </div>
</template>

<script>
import * as cocoSsd from '@tensorflow-models/coco-ssd';

export default {
    name: 'LiveStream',
    props: {
        imageSrc: {
            type: String,
            required: true
        },
        centered: {
            type: Boolean,
            default: false
        }
    },

    data() {
        return {
            model: undefined,
            liveView: undefined,
            children: []
        }
    },

    mounted() {
        this.liveView = document.getElementById('liveView');
        this.loadModel();
    },

    methods: {
        loadModel() {
            cocoSsd.load().then(model => {
                this.model = Object.freeze(model);
                console.log('Model loaded');
                this.predict();
            }).catch(error => {
                console.error('Error loading model:', error);
            });
        },

        predict() {
            const image = document.querySelector('img');
            if (this.model && image.complete && image.naturalWidth !== 0 && image.naturalHeight !== 0) {
                console.log('Predicting...');
                this.model.detect(image).then(predictions => {
                    this.highlightObjects(predictions);
                    console.log('Predictions: ', predictions);
                }).catch(error => {
                    console.error('Error predicting:', error);
                });
            } else {
                console.log('Image not ready for prediction');
            }
            window.requestAnimationFrame(this.predict);
        },

        highlightObjects(predictions) {
            // Remove any highlighting we did previous frame.
            for (let i = 0; i < this.children.length; i++) {
                this.liveView.removeChild(this.children[i]);
            }
            this.children.splice(0);

            // For each prediction we want to draw one box
            for (let n = 0; n < predictions.length; n++) {
                // If we are over 70% sure we are sure we classified it right, draw it!
                if (predictions[n].score > 0.7) {
                    const p = document.createElement('p');
                    p.innerText = predictions[n].class + ' - with '
                        + Math.round(parseFloat(predictions[n].score) * 100)
                        + '% confidence.';
                    p.style = 'margin-left: ' + predictions[n].bbox[0] + 'px; margin-top: '
                        + (predictions[n].bbox[1] - 10) + 'px; width: '
                        + (predictions[n].bbox[2] - 10) + 'px; top: 0; left: 0;';

                    const highlighter = document.createElement('div');
                    highlighter.setAttribute('class', 'highlighter');
                    highlighter.style = 'left: ' + predictions[n].bbox[0] + 'px; top: '
                        + predictions[n].bbox[1] + 'px; width: '
                        + predictions[n].bbox[2] + 'px; height: '
                        + predictions[n].bbox[3] + 'px;';

                    this.liveView.appendChild(highlighter);
                    this.liveView.appendChild(p);
                    this.children.push(highlighter);
                    this.children.push(p);
                    console.log('Highlighting:', predictions[n].class);
                }
            }
        }
    }
}
</script>

<style>
.camView {
    position: relative;
    float: left;
    width: calc(100% - 20px);
    margin: 10px;
    cursor: pointer;
}

.camView p {
    position: absolute;
    padding: 5px;
    background-color: rgba(255, 111, 0, 0.85);
    color: #FFF;
    border: 1px dashed rgba(255, 255, 255, 0.7);
    z-index: 2;
    font-size: 12px;
}

.highlighter {
    background: rgba(0, 255, 0, 0.25);
    border: 1px dashed #fff;
    z-index: 1;
    position: absolute;
}
</style>