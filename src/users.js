import axios from 'axios'
import vars from './vars'

function getNames(users) {
    let ids = users.map(user => user.viewer_id);
    axios.get(`https://api.vk.com/method/users.get?access_token=${vars['access_token']}&user_ids=${ids}`).then(
        response => {
            for (let i = 0; i < users.length; i++) {
                users[i].name = response.data.response[i].first_name;
            }
            return users;
        },
        error => console.log(error)
    );
}

export default getNames;